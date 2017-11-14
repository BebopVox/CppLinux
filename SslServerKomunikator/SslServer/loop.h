#ifndef LOOP2_H
#define LOOP2_H

#include <cstring> // strlen
#include <string>
#include <vector>

#include <iostream> // cin, cout
#include <sstream>  // std::ostringstream

#include <openssl/ssl.h>

#include <cstring> // strlen
#include <string>
#include <vector>
// timestamp time.h
#include <ctime>

// base64
#include "base64.h"
// md5
#include "md5.h"
// db
#include "db.h"

using namespace std;

class Loop{
public:
	// Mysql connect database
	DB db;

	// logs
	ostringstream logi;
	// Authenticated user id
	long long userID = 0;
	string userEmail = "";
	// Divider hash
	string hash = "-----[ABCKGB123321BGKCBA]-----\r\n";
	// Count sent emails
    long long sentEmails = 0;

	Loop();
	// Generate new hash
	string newHash();
	unsigned long getMicrotime();
	// Loop functions
	string getCMD(string buff);
	string replaceAll(string s, string search, string replace);
	bool Contain(std::string str, std::string search);
	vector<string> split(string s, char delim);
	string getAccountInfo();
	string getOnlineUsers();
	string getAds(long long id);
	bool validEmail(string email);
	bool banIP(string IP);
	bool sslError(SSL *ssl, int received);
	string currentDateTimeSMTP();

	// Send to client
	bool sendMsg(string msg, SSL *ssl);
	// Authenticate
	bool Authenticate(string email, string pass);
	// Commands
	bool Auth(string buff, SSL *ssl, string ipAddress);
	// Get command all
	int getCmdAll(string buff, SSL *ssl);
	// Create full message
	string createMessage();

private:	
	// Commands limit
	int cmdLimit = 100;
	// Current commands
	int cmdCnt = 0;		

	// Message
	string from = "";
	string from_name = "";
	string from_email = "";
	string subject = "";
	vector<string> to;
	vector<string> bcc;
	vector<string> to_emails;
	vector<string> bcc_emails;
	vector<string> to_names;
	vector<string> bcc_names;
	vector<string> data;
	vector<vector<string>> files;
	
	// getMessages
	string mimeMessage = "";

	// Disable files
	int disableFiles = 0;	
	// Full message
	string xMessage = "";
};
#endif // LOOP2_H