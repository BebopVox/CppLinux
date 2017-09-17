#ifndef DNSRECORDS_H
#define DNSRECORDS_H
/*
Compile with:
-lresolv
*/

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <resolv.h>
#include <netdb.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>

#include <iostream>
#include <regex>
// ip address
#include <sstream>
#include <arpa/inet.h>
// find
#include <algorithm>

#define N 4096
#define MST (-2)

using namespace std;

class DnsRecords
{
public:
    DnsRecords();
    bool DnsSPFvalidIP(string host, string ip);
    void DnsMX(std::string domain);
    vector<string> DnsTXT(std::string domain);

    vector<string> getMX(std::string email, int show, int logToFile);
    std::string hostnameIP(std::string hostname);
    bool validIPv4(const string& str);
    bool validIPv6(const string& str);
    vector<string> splitDelimiter(string str, string delim);
};

#endif // DNSRECORDS_H
