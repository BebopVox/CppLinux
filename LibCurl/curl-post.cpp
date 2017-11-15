#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>


int main()
{

curl_global_init( CURL_GLOBAL_ALL );
CURL * myHandle = curl_easy_init ( );

// Set up a couple initial paramaters that we will not need to mofiy later.
curl_easy_setopt(myHandle, CURLOPT_USERAGENT, "Mozilla/4.0");
curl_easy_setopt(myHandle, CURLOPT_AUTOREFERER, 1 );
curl_easy_setopt(myHandle, CURLOPT_FOLLOWLOCATION, 1 );
curl_easy_setopt(myHandle, CURLOPT_COOKIEFILE, "");

// Visit the login page once to obtain a PHPSESSID cookie
curl_easy_setopt(myHandle, CURLOPT_URL, "http://www.google.org/logino/");
curl_easy_perform( myHandle );


// Now, can actually login. First we forge the HTTP referer field, or HTS will deny the login
curl_easy_setopt(myHandle, CURLOPT_REFERER, "http://www.google.org/logino/");
// Next we tell LibCurl what HTTP POST data to submit
char *data="username=your_username_here&password=your_password_here";
curl_easy_setopt(myHandle, CURLOPT_POSTFIELDS, data);
curl_easy_perform( myHandle );

curl_easy_cleanup( myHandle );


return 0;
}
