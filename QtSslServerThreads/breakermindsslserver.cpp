/*
 * Install:
 *  apt-get install openssl libssl-dev
 *
 * Add to .pro:
 *  LIBS += -lssl -lcrypto
 *
 * Set linux max proccess limit (1 per MB) 2GB
 * ulimit -u 2048
 *
 * Show limits
 * ulimit -a
 * ulimit -u
 *
 */
#include "breakermindsslserver.h"

#include <iostream>
// file
#include <fstream>
// server
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
// pthread
#include <pthread.h>

using namespace std;

BreakermindSslServer::BreakermindSslServer()
{
    cout << "Run server with Start(PortNumber) Files: certificate.crt, private.key " << endl;
}

int BreakermindSslServer::create_socket(int port)
{
    int s;
    int opt = 1;
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

void BreakermindSslServer::ShowCerts(SSL* ssl)
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

void BreakermindSslServer::init_openssl()
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    // ERR_load_crypto_strings();
}

void BreakermindSslServer::cleanup_openssl()
{
    EVP_cleanup();
}

SSL_CTX *BreakermindSslServer::create_context()
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

void BreakermindSslServer::configure_context(SSL_CTX *ctx, std::string Certificate, std::string CertificateKey)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);
    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, Certificate.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, CertificateKey.c_str(), SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
    }

}

void BreakermindSslServer::SaveToFile(const char* val){
    ofstream myfile;
    // myfile.open ("email.txt", ios::out | ios::app | ios::binary);
    myfile.open ("m2.txt", ios::out | ios::app );
    myfile << val << " Writing this to a file.Writing this to a file.Writing this to a file. \n " << val << endl;
    myfile.close();
    cout << val << " Class methods works File has been saved!\n";
}

void BreakermindSslServer::Start(int Port, string Certificate, string CertificateKey)
{
    cout << "Starting server ..." << endl;

    pthread_t thread1;

    int i = 1, ret;

    // Initialize ssl
    SSL_library_init();

    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();

    configure_context(ctx, Certificate, CertificateKey);

    sock = create_socket(Port);

    /* Handle connections */
    while(1) {
        // user id
        int users = 0;

        struct sockaddr_in addr;
        uint len = sizeof(addr);

        const char reply[] = "220 Hello from server\n";

        cout << "Waiting for connections ..." << endl;

        // error != 0
        int client = accept(sock, (struct sockaddr*)&addr, &len);
        printf("Connection: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

        // new thread proccess
        struct thread_info tinfo;
        tinfo.client = client;
        tinfo.ctx = ctx;
        tinfo.th_id = 5;

        // error -1, ok > 0
        ret =  pthread_create(&thread1, NULL, &worker_thread, &tinfo);
        if(ret != 0) {
                std::string s = to_string(i);
               cout << "Error: pthread_create() failed " <<  "\n ";
                exit(EXIT_FAILURE);
        }else{
            std::string s = to_string(i);
             cout << "In main: creating thread " << " \n";
        }

        if (ret > 0) {
            fprintf(stderr, "Mam mowego klienta, pid=%d\n", ret);
            continue;
        }

        if (client < 0) {
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }

        // printf("SSL pid %s", getpid());
    }

    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl();
}

void *BreakermindSslServer::worker_thread(void *arg)
{
    struct thread_info *tinfo = (thread_info *)arg;
    BreakermindSslServer ss = BreakermindSslServer();
    ss.ServerLoop(tinfo->ctx,tinfo->client);

    /*
    int j = 0;
    while(j < 25){
        // cout << "This is worker_thread() "  << i << "\n";
        printf("This is worker_thread #%ld loop: %ld \n", (long)i, (long)j);
        usleep((long)i*1000000);
        j++;
    }
    */
    pthread_exit(NULL);
}

// Server mail loop if You need send data with ovveride this method !!!
void BreakermindSslServer::ServerLoop(SSL_CTX *ctx, int client){

    const char reply[] = "220 Hello from server\n";

    // buffer
    const int readSize = 8192;
    char buffer[8192];

    int received, count = 0;
    int TotalReceived = 0;

    SSL *ssl;
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client);
    // ShowCerts(ssl);

    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
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

        const char reply1[] = "250 Next Command MAIL FROM:\n";
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

        char endstr[] = "...";
        std::string buf = std::string(buffer);
        std::string dot = std::string(endstr);
        // buf.substr(0, buf.size()-1);
        buf = buf.substr(0, 3);
        dot = dot.substr(0, 3);

        // std::cout << "Compare " << buf.size() << " z " << dot.size() << " end ";
        // std::cout << "Compare " << std::string(buffer) << " z " << std::string(dot) << " end ";

        if( std::string(endstr) == std::string(buf) ){
            z = 0;
            printf("%s\n", "Close connection with client ");
            SSL_shutdown(ssl);
            close(client);
            // kill chld proccess
            // kill(getpid(), SIGKILL);
            pthread_exit(NULL);
        }else{
            printf("%s\n", "Working connection");
        }
        sslError(ssl,received);
    }

    //printf("SSL pid %s", getpid());
    //SSL_free(ssl);
    //close(client);
}

// Check ssl error
void BreakermindSslServer::sslError(SSL *ssl, int received){
    const int err = SSL_get_error(ssl, received);
    // const int st = ERR_get_error();
    if (err == SSL_ERROR_NONE) {
        std::cout<<"SSL_ERROR_NONE:"<<SSL_ERROR_NONE<<std::endl;
        // SSL_shutdown(ssl);
    } else if (err == SSL_ERROR_WANT_READ ) {
        std::cout<<"SSL_ERROR_WANT_READ:"<<SSL_ERROR_WANT_READ<<std::endl;
        SSL_shutdown(ssl);
        //kill(getpid(), SIGKILL);
        pthread_exit(NULL);
    } else if (SSL_ERROR_SYSCALL) {
        std::cout<<"SSL_ERROR_SYSCALL:"<<SSL_ERROR_SYSCALL<<std::endl;
        SSL_shutdown(ssl);
        //kill(getpid(), SIGKILL);
        pthread_exit(NULL);
    }
}
