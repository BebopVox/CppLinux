#ifndef DB_H
#define DB_H

// #include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

// time
#include <time.h>
#include <stdio.h>

// mysql
#include "mysql.h"
// #include "mysql_driver.h"
// #include "mysql_error.h"

// errorno: std::strerror(errno)
#include <errno.h>
#include <cstring>

using namespace std;

extern "C" size_t decode_html_entities_utf8(char *dest, const char *src);

class DB 
{
public:
	MYSQL *connect, mysql;
	std::string ServerHostname;
	DB();	
	void ServerHost(string serverHost);
	bool Connect(string host, string port, string user, string pass, string db);	
	void Close();

	// date time
	std::string currentDateTime();
	char * currentDateTimeSMTP();
	int changeMessageStatus(int deliveredID);
	int changeMessageStatusError(int deliveredID);
	void SendMessages(int treadLimit);

	// Database sslbreakermindserver
	vector<string> getDKIM(std::string email);
	int getMxPort(std::string host);
	int addMxPort(string host, int port);
	void CreateTables();
	vector<string> splitDelimiter(string str, string delim);
	bool validAuthIP(string email, std::string ip);
	bool isMailboxExists(string email);
	bool isLocalDomain(string email);
	bool isAuthenticate(string email, string pass);
	bool checkDDOSLimit(int iplimit, int minutes);
	bool checkBanIpLimit(int limit, int minutes, string ip_address);
	unsigned long long LastInsertID();
	unsigned long long InsertBanIP(string ip);
	
	// Insert message
	unsigned long long InsertMsg(string efrom, string efromname, string subject, string html);
	unsigned long long InsertMsgSingle(string efrom, string efromname, string eto, string etoname, string subject, long long msgId);

	// add slash quotes ' "
	string Quotes(string s);
	string reQuotes(string s);
	// Entities
	string entitiesEncode(string str);
	string entitiesDecode(string str);

	bool validEmail(std::string email);
	unsigned long long  userID(string email);
	vector<vector<string>> getMessages(string fromEmail, string toEmail, int limit);

};

#endif