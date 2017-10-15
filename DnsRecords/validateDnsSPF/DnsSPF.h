#ifndef DNSSPF_H
#define DNSSPF_H

#include <iostream>
#include <string>
#include <string.h> //memset
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h> //for exit(0);
#include <errno.h> 
#include <fstream>
#include <time.h>
#include <vector>
#include <regex>
// ip address
#include <sstream>
// network
#include <arpa/inet.h>
#include <netinet/in.h>
#include <resolv.h>
// str sockadr, hostnet
#include <netdb.h>
// find, find vectors
#include <algorithm>
// perror
#include <errno.h>

using namespace std;

class DnsSPF
{
public:
    bool DnsSPFvalidIP(string host, string ip);
    vector<string> getDnsMX(std::string email);
    vector<string> getDnsTXT(std::string domain);
    vector<string> getDnsSPF(std::string domain);
    std::string hostname_to_ip(std::string hostname);
    std::string ip_to_hostname(std::string ip);
    bool is_ipv4_address(const string& str);
    bool is_ipv6_address(const string& str);
    vector<string> splitDelimiter(string str, string delim);
    // str
    bool Contain(std::string str, std::string search);    
    char* replace_char(char* str, char find, char replace);
    string RemoveSpaces(string source);
    bool validSpfIP(string ipAddress, string domain, string spf, vector<string> redirects)
    string replaceAll(string s,string search,string replace);    
    // search string in vector
    bool inVector(std::vector<string> v, string search);
    // validate ip range
    bool validateRangeIP(string ipsubnet,string ip);
    vector<string> split(string s, char delim);
};

#endif // DNSSPF_H
