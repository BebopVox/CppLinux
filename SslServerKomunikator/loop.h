#ifndef LOOP2_H
#define LOOP2_H

#include <cstring> // strlen
#include <string>
#include <vector>
#include <iostream>
#include <openssl/ssl.h>

using namespace std;

class Loop{
public:
	Loop();
	// ~Loop();
	// Loop functions
	string getCMD(string buff);
	string replaceAll(string s, string search, string replace);
	bool Contain(std::string str, std::string search);
	vector<string> split(string s, char delim);
	string getAccountInfo(long long id);
	string getAds(long long id);
	bool validEmail(string email);
	bool banIP(string IP);
	bool sslError(SSL *ssl, int received);

	// Send to client
	bool sendMsg(string msg, SSL *ssl);
	// Authenticate
	bool Authenticate(string email, string pass);
	// Commands
	bool Auth(string buff, SSL *ssl, string ipAddress);
	// Get command all
	int getCmdAll(string buff, SSL *ssl);

private:
	int cmdLimit = 100;
	int cmdCnt = 0;
	string from = "";
	string subject = "";
	vector<string> to;
	vector<string> bcc;
	vector<string> data;
	vector<vector<string>> files;
};
#endif // LOOP2_H