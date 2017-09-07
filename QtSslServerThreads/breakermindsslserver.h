#ifndef BREAKERMINDSSLSERVER_H
#define BREAKERMINDSSLSERVER_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>
#include <cstring>

using namespace std;

struct thread_info {    /* Used as argument to thread_start() */
           // pthread_t client;        /* ID returned by pthread_create() */
           // SSL       *ssl;       /* Application-defined thread # */
           string    th_id;      /* From command-line argument */
           SSL_CTX *ctx;
           int client;
       };

class BreakermindSslServer{
    public:
        BreakermindSslServer();
        // Set ssl connection
        SSL_CTX *create_context();
        int create_socket(int port);
        void ShowCerts(SSL* ssl);
        void init_openssl();
        void cleanup_openssl();
        void configure_context(SSL_CTX *ctx, std::string Certificate, std::string CertificateKey);
        // Run server
        void Start(int Port, std::string Certificate, std::string CertificateKey);
        // Save to file
        void SaveToFile(const char* val);
        static void *worker_thread(void *arg);
        void sslError(SSL *ssl, int received);

    protected:
        // Main loop send and receive data from clients here
        void ServerLoop(SSL_CTX *ctx, int client);

    private:
        SSL* ssl;
};
#endif // BREAKERMINDSSLSERVER_H
