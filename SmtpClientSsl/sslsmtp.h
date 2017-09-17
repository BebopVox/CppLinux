#ifndef SSLSMTP_H
#define SSLSMTP_H

#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define FAIL    -1

using namespace std;

class SslSMTP
{
private:
    int Port = 587;
public:
    SslSMTP(int port);
    // Create mime message and send
    void From(string email);
    void ReplyTo(string email);
    void addTo(string email);
    void addHtml(string html);
    void addAttachment(string file);
    int Send();
    // ssl client
    bool Send(string hostnameMX, string from, string to, string mimedata);
    int OpenConnection(const char *hostname, int port);
    SSL_CTX* InitCTX(void);
    void ShowCerts(SSL* ssl);
};

#endif // SSLSMTP_H
