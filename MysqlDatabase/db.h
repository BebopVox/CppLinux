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
// sslsmtpex
#include "sslsmtpex.h"

using namespace std;

class DB 
{
public:
	MYSQL *connect, mysql;
	std::string ServerHostname;
	DB();	
	void ServerHost(string serverHost);
	bool Connect(string host, string user, string pass, string db, string port);	
	void Close();
	vector<vector<string>> getMessagesToSend(int limit);
	// update with threadID
	vector<vector<string>> getMessagesToSendX(int limit);
	// date time
	std::string currentDateTime();
	char * currentDateTimeSMTP();
	int changeMessageStatus(int deliveredID);
	void SendMessages(int treadLimit);
};

#endif
