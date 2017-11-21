#include <string>
#include <iostream>
#include "curl-license.h"
#include <curl/curl.h>

using namespace std;

int main(){

LicenseCurl lic;

cout << lic.checkKey("key");

cout << "Works " << endl; 
}
