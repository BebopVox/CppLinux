#ifndef DNSSPF_H
#define DNSSPF_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <resolv.h>
#include <netdb.h>
#include<string.h> //memset
#include<stdlib.h> //for exit(0);
// #include<sys/socket.h>
#include<errno.h> //For errno - the error number
#include<netdb.h> //hostent
#include<arpa/inet.h>

#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>

using namespace std;

class DnsSPF
{
public:
    bool DnsSPFvalidIP(string host, string ip);
    void DnsMX(std::string domain);
    vector<string> DnsMX2(std::string email);
    vector<string> DnsTXT(std::string domain);
    std::string hostname_to_ip(std::string hostname);
    std::string ip_to_hostname(std::string ip);
    bool is_ipv4_address(const string& str);
    bool is_ipv6_address(const string& str);
    vector<string> splitDelimiter(string str, string delim);
    // str
    bool Contain(std::string str, std::string search);    
    char* replace_char(char* str, char find, char replace);
    void RemoveSpaces(char* source);
    bool validSpfIP(string ip, string domain, string spf);
    string replaceAll(string s,string search,string replace);
    vector<string> getDnsTXTSPF(std::string domain);
};

#endif // DNSSPF_H
