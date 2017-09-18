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

// BreakermindLib
#include "BreakermindLib/Base64/base64.h"

// apt-get install libssl-dev openssl
// g++ -o output main.cpp -lssl -lcrypto

using namespace std;

// main - create SSL context and connect
int main(int count, char *strings[])
{
    // base64 example
    // BreakermindLib base64
    const std::string str =
        "Breakermind Hello string\r\n"
        "http://breakermind.com\n"
        "passion for data\n";
    std::string encoded = base64_encode(str);
    std::string decoded = base64_decode(encoded);
    cout << encoded;
    cout << decoded;

    // return 0;

    /*
    DnsRecords dns = DnsRecords();
    vector<string> mx = dns.getMX("hello@gmail.com",1,1);

    for(int i = 0; i < mx.size(); i++){
        cout << "MX Hosts " <<  mx.at(i) << endl;
        // Send email with smtp no auth no inline(only in html as base64 img) default ssl port 587
        // SslSMTP mime = SslSMTP(25);
    }
    */

    cout << "Start smtp\r\n";
    // SslSMTP smtp = SslSMTP(25);
    // cout << smtp.Date(1) << endl;
    // smtp.Send("aspmx.l.google.com", "", "", "");
    // add files path

    // Send email to
    std::string recipient = "info@qflash.pl";
    // Get mx hostname from dns for recipient email address
    DnsRecords dns = DnsRecords();
    // vector<string> mx = dns.getMX("info@qflash.pl",0,0);
    vector<string> mx = dns.getMX(recipient,0,0);
    // Send email to each hostname or port (if was send error)
    int mailsend = 0;
    for(int i = 0; i < mx.size(); i++){
        if(mailsend == 0){
            std::string mxhost = mx.at(i);
            cout << "MX Host " <<  mxhost << endl;
            // SslSMTP smtp = SslSMTP("qflash.pl", 25);
            SslSMTP smtp = SslSMTP(mxhost, 25);
            vector<string> files;
            files.push_back("file9.jpg");
            files.push_back("filek.pdf");
            // send email
            // int ok = smtp.Send("<hello@breakermind.com>", "<info@qflash.pl>", "<hello@breakermind.com>", "Hello111111=2C_czy_um=F3wisz_si=EA_ze_mn=B1=3F?=", "Wiadomosć tekstowa dla usera", "<h1>Hello from html msg.</h1>", files);
            mailsend = smtp.Send("<hello@breakermind.com>", recipient, "<hello@breakermind.com>", "Hello111111=2C_czy_um=F3wisz_si=EA_ze_mn=B1=3F?=", "Wiadomosć tekstowa dla usera", "<h1>Hello from html msg.</h1>", files);
            if(mailsend){
                cout << "Email has been sent! Port 25" << endl;
            }else{
                // SslSMTP smtp = SslSMTP("qflash.pl", 587);
                SslSMTP smtp = SslSMTP(mxhost, 587);
                vector<string> files;
                files.push_back("file9.jpg");
                files.push_back("filek.pdf");
                // send email
                mailsend = smtp.Send("<hello@breakermind.com>", "<info@qflash.pl>", "<hello@breakermind.com>", "Hello111111=2C_czy_um=F3wisz_si=EA_ze_mn=B1=3F?=", "Wiadomosć tekstowa dla usera", "<h1>Hello from html msg.</h1>", files);
                cout << "Email has been sent! Port 587" << endl;
            }
        }
    }

    cout << "\r\nStop smtp";

    // jSMTP sample example
    // SslClient c = SslClient();
    // c.Send("qflash.pl","{\"from\":[{\"name\":\"Zenobiusz\",\"email\":\"hello@fxstar.eu\"}]}","{\"rcpt\":[{\"name\":\"Zenobiusz\",\"email\":\"hello@fxstar.eu\"}]}","{\"subject\":\"Jakiś temat wiadomosci\"}","{\"html\":\"Jakas tresc wiadomosci\"}","{\"header\":[{\"row\":\"Date 2017-06-09 22:33:55\"}]}","{\"files\":[{\"file\":\"file1.jpg\"},{\"file\":\"img.zip\"},{\"file\":\"cv.pdf\"}]}", "{\"file\":[{\"name\":\"file1.jpg\",\"content\":\"fileContentHere\"}]}{\"file\":[{\"name\":\"img.zip\",\"content\":\"fileContentHere\"}]}{\"file\":[{\"name\":\"cv.pdf\",\"content\":\"fileContentHere\"}]}");

}
