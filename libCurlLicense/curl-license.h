#ifndef CURL_CLIENT_H
#define CURL_CLIENT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>

using namespace std;

class LicenseCurl{

public:	
	LicenseCurl();	
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	bool checkKey(string key);

};

#endif  // CURL_CLIENT_H