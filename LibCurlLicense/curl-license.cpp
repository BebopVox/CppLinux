#include "curl-license.h"

LicenseCurl::LicenseCurl(){}

size_t LicenseCurl::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool LicenseCurl::checkKey(string key){
	try{
		CURL *curl;
		CURLcode res;
		std::string readBuffer;
		std::string error = "";
		std::string url = "https://breakermind.com/license/index.php?app=1&key=" + key;

		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl = curl_easy_init();
		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			// Skip verification
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
			// Save output to string readBuffer
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			// Follow redirects
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
			// POST
			//curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0");
			//curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1 );    
			//curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
			res = curl_easy_perform(curl);
			if(res != CURLE_OK){
				cout << "License verificatio curl_easy_perform() failed: " <<  curl_easy_strerror(res) << endl;	
				return 1;
			}	  
			curl_easy_cleanup(curl);
			// Show output
			std::cout << readBuffer << std::endl;
		}
		curl_global_cleanup();	
		if(readBuffer == "0"){
			return 0;
		}
		// Show output
		std::cout << readBuffer << std::endl;
		return 1;
	}catch(std::exception &e){
		return 1;
	}
}