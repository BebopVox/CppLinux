#ifndef SSLSMTP_H
#define SSLSMTP_H

#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <string>
#include <resolv.h>
#include <netdb.h>
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
// quoted
#include <iomanip>
#include <sstream>
// socket time out
#include <sys/types.h>
#include <sys/socket.h>

// fstream
#include <fstream>
#include <cerrno>
// signals errors
#include <signal.h>

#define FAIL    -1

using namespace std;

class SslSMTP
{
private:
    int Port = 25;
    std::string HostnameMX = "localhost";
public:
    SslSMTP(string hostnameMX, int port);
    // Create mime message and send
    int Send();
    // ssl client
    bool Send(string from, string to, string replyto, string subject, string msg, string msghtml, vector<string> files);
    int OpenConnection(const char *hostname, int port);
    void socketTimeout(int sd, int timeoutseconds);
    SSL_CTX* InitCTX(void);
    void ShowCerts(SSL* ssl);
    void sslError(SSL *ssl, int received);
    void quoted(std::string str);
    string Date(bool utc = 0);
    string fileBasename(string path);
    std::string getFileContent(const std::string& path);
    std::string get_file_contents(const char *filename);
    // file mime type
    const char* GetMimeTypeFromFileName( char* szFileExt);
    string GetFileExtension(const std::string& FileName);
    bool Contain(std::string str, std::string search);

    static const char MimeTypes[][2][128];
};

#endif // SSLSMTP_H
