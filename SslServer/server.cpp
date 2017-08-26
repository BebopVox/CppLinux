/*

Connect to server:
telnet-ssl -z ssl  127.0.0.1 3333
openssl s_client -connect 127.0.0.1:3333

Update sources and install first 
apt-get update

// g++
apt-get install g++ bulid-essential

//  open ssl
apt-get install openssl libssl-dev 

// mysql (don't need here)
apt-get install libmysql++ libmysql++-dev libmysql++-doc

Compile with: 
g++ -o server server.cpp -lssl -lcrypto

Connect:
openssl s_client -connect 127.0.0.1:3333
telnet-ssl -z ssl 127.0.0.1 3333

*/
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <pthread.h>
#include <errno.h>
#include <signal.h>

// const SSL_METHOD *TLSv1_2_method(void);
// const SSL_METHOD *TLSv1_2_server_method(void);
// const SSL_METHOD *TLSv1_2_client_method(void);

const int readSize = 8192;
// buffer string
char buffer[8192];
// Close connection string
char end[] = "...";

int received, count = 0;
int TotalReceived = 0;
// const char * opt = "TRUE";
int opt = 1;
// new "thread" proccess
pid_t pid;
int currpid = 0 ;

#define PORT 3333
int create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
	perror("Unable to create socket");
	exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if( setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }


    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
	perror("Unable to bind");
	exit(EXIT_FAILURE);
    }

    if (listen(s, 2) < 0) {
	perror("Unable to listen");
	exit(EXIT_FAILURE);
    }

    return s;
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);   /* Get certificates (if available) */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}

void init_openssl()
{ 
    SSL_library_init(); 
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
    // ERR_load_crypto_strings();
}

void cleanup_openssl()
{
    EVP_cleanup();
}

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    method = SSLv23_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
    	perror("Unable to create SSL context");
    	ERR_print_errors_fp(stderr);
    	exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "certificate.crt", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
	exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "private.key", SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
	exit(EXIT_FAILURE);
    }

}

int main(int argc, char **argv)
{
    // Initialize ssl
    SSL_library_init();

    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();

    configure_context(ctx);

    sock = create_socket(PORT);

    /* Handle connections */
    while(1) {
        // user id
        int users = 0;

        struct sockaddr_in addr;
        uint len = sizeof(addr);
        
        // max users
        SSL *ssl;

        const char reply[] = "220 Hello from server\n";
        const char reply1[] = "250 Next Command MAIL FROM:\n";

        int client = accept(sock, (struct sockaddr*)&addr, &len);
        printf("Connection: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

        pid = fork();
        if (pid > 0) {
            currpid = pid;
            fprintf(stderr, "Mam mowego klienta, pid=%d\n", currpid);
            continue;
        }

        if (client < 0) {
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }

        // thread need here
        // pthread_t t;
        // pthread_create(&t, NULL, call_from_thread, NULL);
        
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);

        ShowCerts(ssl);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        }
        else {
            SSL_write(ssl, reply, strlen(reply));
        }

        // Read from client
        received = SSL_read (ssl, buffer, readSize);
        if (received > 0)
        {
            TotalReceived += received;
            printf("PID %i Buffsize - %i - %.*s \n", getpid(), received, received, buffer);
        }

        int z = 1;
        while(z == 1){
            // Send to client
            SSL_write(ssl, reply1, strlen(reply1));

            // Read from client
            received = SSL_read (ssl, buffer, readSize);
            if (received > 0)
            {
                TotalReceived += received;                                                
                printf("PID %i Buffsize - %i - %.*s \n", getpid(), received, received, buffer);
            }        
            // buffer to string                        
            printf("Client send: %s\n", buffer);                         

            std::string buf = std::string(buffer);
            std::string end = std::string(end);
            // buf.substr(0, buf.size()-1);
            buf = buf.substr(0, 3);
            ggg = end.substr(0, 3);

            std::cout << "Compare " << buf.size() << " z " << ggg.size() << " end ";
            std::cout << "Compare " << std::string(buffer) << " z " << std::string(end) << " end ";

            if( std::string(end) == std::string(buf) ){
                printf("%s\n", "End connection ");
                z = 0;
                SSL_shutdown(ssl);
            }else{
                printf("%s\n", "Working connection");
            }            
        }

        
        // execl(kill( pid, 1 ));        
        
        

        printf("SSL pid %s", getpid());
        SSL_free(ssl);
        printf("Client pid %s", getpid()); 
        close(client);                  
        printf("Kill pid %s", getpid());
        // kill process 
        // kill(getpid(), SIGKILL);
        // kill(getpid(), SIGTERM);        

        SSL_free(ssl);
        close(client);        
        exit(1);
        close(sock);
        SSL_CTX_free(ctx);
        cleanup_openssl();
    }

    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl();
}


/*

#include <openssl/ssl.h>


// Inicjalizacja open ssl wymagana
 int SSL_library_init(void);
 #define OpenSSL_add_ssl_algorithms()    SSL_library_init()
 #define SSLeay_add_ssl_algorithms()     SSL_library_init()

 SSL_load_error_strings();                // readable error messages
 SSL_library_init();                      /// initialize library

// then
SSL_CTX *SSL_CTX_new(const SSL_METHOD *method);

 const SSL_METHOD *TLSv1_2_method(void);
 const SSL_METHOD *TLSv1_2_server_method(void);
 const SSL_METHOD *TLSv1_2_client_method(void);


 long SSL_CTX_set_options(SSL_CTX *ctx, long options);
 long SSL_set_options(SSL *ssl, long options);

 long SSL_CTX_clear_options(SSL_CTX *ctx, long options);
 long SSL_clear_options(SSL *ssl, long options);

 long SSL_CTX_get_options(SSL_CTX *ctx);
 long SSL_get_options(SSL *ssl);

 long SSL_get_secure_renegotiation_support(SSL *ssl);
 */
