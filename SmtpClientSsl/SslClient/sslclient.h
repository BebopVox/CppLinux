#ifndef SSLCLIENT_H
#define SSLCLIENT_H

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define FAIL    -1

using namespace std;

class SslClient
{
public:
    bool Send(string hostnameMX, string from, string to, string subject, string html, string header, string files, string filesdata);
    int OpenConnection(const char *hostname, int port);
    SSL_CTX* InitCTX(void);
    void ShowCerts(SSL* ssl);
};

#endif // SSLCLIENT_H
