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
    vector<string> DnsTXT(std::string domain);
    std::string hostname_to_ip(std::string hostname);
    bool is_ipv4_address(const string& str);
    bool is_ipv6_address(const string& str);
};

#endif // DNSSPF_H
