#ifndef BREAKERMINDSSLSERVER_H
#define BREAKERMINDSSLSERVER_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>
#include <cstring>

using namespace std;

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

    protected:
        // Main loop send and receive data from clients here
        void ServerLoop(SSL *ssl);

    private:
        SSL* ssl;
};
#endif // BREAKERMINDSSLSERVER_H
