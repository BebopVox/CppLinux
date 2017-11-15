// apt-get install curl libcurl3 libcurl3-dev curl-dev
// Compile 
//  g++ -o start curl.cpp -lcurl -L/usr/incluse/curl

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <stdio.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://google.com?id=USER123456");
    #ifdef SKIP_PEER_VERIFICATION    
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    #endif 
    #ifdef SKIP_HOSTNAME_VERIFICATION    
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    #endif    
    // Save output to string readBuffer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    // Follow redirects
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );
    // POST
    //curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0");
    //curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1 );    
    //curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    curl_easy_cleanup(curl);

    // Show output
    std::cout << readBuffer << std::endl;    
  }
  curl_global_cleanup();
  return 0;
}
