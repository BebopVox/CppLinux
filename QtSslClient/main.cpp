// ssl_client.c

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define FAIL    -1

// OpenConnection - create socket and connect to server.
int OpenConnection(const char *hostname, int port)
{   int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ( (host = gethostbyname(hostname)) == NULL )
    {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
        addr.sin_addr.s_addr = *(long*)(host->h_addr);
        if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
        {
            close(sd);
            perror(hostname);
            abort();
        }
        return sd;
}

// InitCTX - initialize the SSL engine.
SSL_CTX* InitCTX(void)
{   const SSL_METHOD *method;
    SSL_CTX *ctx;

    SSL_library_init();
    SSL_load_error_strings();			// Bring in and register error messages
    OpenSSL_add_all_algorithms();		// Load cryptos

    method = SSLv23_client_method();	// Create new client-method instance
    ctx = SSL_CTX_new(method);			// Create new context
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

// ShowCerts - print out the certificates.
void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);	// get the server's certificate
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);							// free the malloc'ed string
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);							// free the malloc'ed string
        X509_free(cert);					// free the malloc'ed certificate copy
    }
    else
        printf("No certificates.\n");
}

// main - create SSL context and connect
int main(int count, char *strings[])
{   SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[1024];
    int bytes;
    char *hostname, *portnum;

    hostname = "qflash.pl";
    portnum = "3333";

    ctx = InitCTX();
    server = OpenConnection(hostname, atoi(portnum));
    ssl = SSL_new(ctx);						// create new SSL connection
    SSL_set_fd(ssl, server);				// attach the socket descriptor
    if ( SSL_connect(ssl) == FAIL )
        ERR_print_errors_fp(stderr);
    else
    {   char *msg = "{\"from\":[{\"name\":\"Zenobiusz\",\"email\":\"email@eee.ddf\"}]}";


        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        ShowCerts(ssl);

        bytes = SSL_read(ssl, buf, sizeof(buf));
        buf[bytes] = 0;
        printf("Received from server: \"%s\n", buf);

        SSL_write(ssl, msg, strlen(msg));

        bytes = SSL_read(ssl, buf, sizeof(buf));
        buf[bytes] = 0;
        printf("Received from server: \"%s\n", buf);

        SSL_free(ssl);
    }
    close(server);
    SSL_CTX_free(ctx);
}
