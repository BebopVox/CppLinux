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
// include client class
#include <sslclient.h>

#define FAIL    -1

// Dns MX
#include <dnsrecords.h>
// SslSMTP
#include <sslsmtp.h>

int main(int count, char *strings[])
{
    cout << "Start smtp\r\n";
    SslSMTP smtp = SslSMTP(25);
    // smtp.Send("aspmx.l.google.com", "", "", "");
    // send email with attachment
    smtp.Send("qflash.pl", "", "", "");
    cout << "\r\nStop smtp";
}
