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

using namespace std;

class DnsSPF
{
public:
    DnsSPF(std::string domain);
    std::string hostname_to_ip(std::string hostname);
};

#endif // DNSSPF_H
