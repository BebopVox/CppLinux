#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <openssl/bio.h>
#include <openssl/ssl.h>

#define DEFAULTPORT "555"
#define CERTIFICATE_FILE "/home/user/c++/server/certificate.pem"
#define PRIVATE_KEY "/home/user/c++/server/certificate.pem"
// openssl dhparam -out /home/user/c++/server/dhserver.pem 512
#define DH_FILE "/home/user/c++/server/dhserver.pem"
#define RESPONSE "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n"

SSL_CTX *server_ssl_initialize_ctx2() {	
	SSL_CTX *ctx;
	BIO *dhbio;

	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	
	ctx = SSL_CTX_new(SSLv23_server_method());
	
	if (!ctx) {
    	perror("Unable to create SSL context");
    	ERR_print_errors_fp(stderr);
    	exit(EXIT_FAILURE);
    }

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "certificate.crt", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
	exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "private.key", SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
	exit(EXIT_FAILURE);
    }
    return ctx;

}

SSL_CTX *server_ssl_initialize_ctx() {	
	SSL_CTX *ctx;
	BIO *dhbio;

	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	ctx = SSL_CTX_new(SSLv23_server_method());
	
	if (!ctx) {
    	perror("Unable to create SSL context");
    	ERR_print_errors_fp(stderr);
    	exit(EXIT_FAILURE);
    }

	if (SSL_CTX_use_certificate_file(ctx, CERTIFICATE_FILE, SSL_FILETYPE_PEM) != 1) {
		fprintf(stderr, "Błąd wczytywania certyfikatu.\n");
		ERR_print_errors_fp(stderr);
		return NULL;
	}
	if(SSL_CTX_use_PrivateKey_file(ctx, PRIVATE_KEY, SSL_FILETYPE_PEM) != 1) {
		fprintf(stderr, "Błąd wczytywania klucza prywatnego.\n");
		ERR_print_errors_fp(stderr);
		return NULL;
	}
	if(SSL_CTX_check_private_key(ctx) != 1){
		fprintf(stderr, "Klucz prywatny zdaje się nienależeć do certyfikatu.\n");
		ERR_print_errors_fp(stderr);
		return NULL;
	}
	if ((dhbio = BIO_new_file(DH_FILE, "r")) == NULL) {
		fprintf(stderr, "Błąd we wczytywaniu parametrów DH. Pomijamy ten krok.\n");
		ERR_print_errors_fp(stderr);
	} else {
		DH *dh = PEM_read_bio_DHparams(dhbio, NULL, NULL, NULL);
		BIO_free(dhbio);
		if (SSL_CTX_set_tmp_dh(ctx, dh) < 0) {
			fprintf(stderr, "Błąd w ustawianiu paremetrów DH. Pomijamy.\n");
			ERR_print_errors_fp(stderr);
		}
	}
	return ctx;
}

void sigchild_handler(int sig) {
	int status;
	pid_t pid;
	pid = wait(&status);
	if (WIFEXITED(status)){
		fprintf(stderr, "Proces%d wrocil z kodem %d.\n", pid, WEXITSTATUS(status));
	}else if (WIFSIGNALED(status)){
		fprintf(stderr, "Proces %d został zabity sygnałem %d.\n", pid, WTERMSIG(status));
	}
}


void sigchild_handler(int sig);
SSL_CTX *server_ssl_initialize_ctx();

int main(int argc, char **argv) {
	char *portbuff;
	int rv;
	BIO *listen_bio;
	SSL_CTX *ctx;
	SSL *ssl;
	char buf[1024];
	int len;
	if (!(ctx = server_ssl_initialize_ctx())) {
		fprintf(stderr, "Niestety.\n");
		exit(1);
	}
	if (argc > 1){
		portbuff = strdup(argv[1]);
	}else{
		portbuff = strdup(DEFAULTPORT);
	}
	signal(SIGCHLD, sigchild_handler);
	listen_bio = BIO_new_accept(portbuff);
	BIO_set_bind_mode(listen_bio,
	BIO_BIND_REUSEADDR);
	if(BIO_do_accept(listen_bio) <= 0) {
		fprintf(stderr, "Błąd w	przygotowaniu do obsługi klientów.\n");
		ERR_print_errors_fp(stderr);
		exit(0);
	}
	while (1) {
		BIO *client_bio = BIO_new_ssl(ctx, 0);
		BIO *buffered_bio;
		BIO_get_ssl(client_bio, &ssl);
		if (!ssl) {
			fprintf(stderr, "Błąd ssl.\n");
			ERR_print_errors_fp(stderr);
			BIO_free_all(listen_bio);
			SSL_CTX_free(ctx);
			exit(1);
		}
		SSL_set_verify(ssl, SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE, NULL);
		SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
		BIO_set_accept_bios(listen_bio, client_bio);
		
		if (BIO_do_accept(listen_bio) <= 0) {
			fprintf(stderr, "Błąd podczas przyjmowania połączenia.\n");
			ERR_print_errors_fp(stderr);
			continue;
		}
		
		client_bio = BIO_pop(listen_bio);
		rv = fork();
		if (rv > 0) {
			fprintf(stderr, "Mam mowego klienta, pid=%d\n", rv);
			continue;
		}
		if (rv == -1) {
			fprintf(stderr, "Błąd w tworzeniu nowego procesu: %s.\n", strerror(errno));
			BIO_free(client_bio);
			continue;
		}
		if (BIO_do_handshake(client_bio) <= 0) {
			fprintf(stderr, "Błąd podczas SSL handshake.\n");
			ERR_print_errors_fp(stderr);
			BIO_free_all(client_bio);
			return 1;
		}
		buffered_bio = BIO_new(BIO_f_buffer());
		client_bio = BIO_push(buffered_bio, client_bio);
		BIO_puts(client_bio, RESPONSE);

		while (1) {
			len = BIO_gets(client_bio, buf, 1024);
			if (len <= 0) {
				fprintf(stderr, "Błąd w czytaniu z gniazda.\n");
				ERR_print_errors_fp(stderr);
				break;
			}
			BIO_write(client_bio, buf, len);
			if ((buf[0] == '\r') || (buf[0] == '\n'))
			break;
		}
		BIO_puts(client_bio, "milo, ze wpadles.\r\n");
		rv = BIO_flush(client_bio);
		BIO_free_all(client_bio);
		exit(0);
	}
	if (portbuff)
	free(portbuff);
	return 0;
}