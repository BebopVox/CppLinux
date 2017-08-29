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
        int create_socket(int port);
        void ShowCerts(SSL* ssl);
        void init_openssl();
        void cleanup_openssl();
        SSL_CTX *create_context();
        void configure_context(SSL_CTX *ctx, std::string Certificate, std::string CertificateKey);
        // Run server
        void Start(int Port, std::string Certificate, std::string CertificateKey);

        // Save to file
        void SaveToFile(const char* val);

        std::string ServerCertificate = "";
        std::string ServerKey = "";

    protected:

    private:
        SSL* ssl;


};
#endif // BREAKERMINDSSLSERVER_H
