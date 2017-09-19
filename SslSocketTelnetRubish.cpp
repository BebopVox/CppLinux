// Ssl
SSL *ssl;

...

// buffer
const int readSize = 8192;
char buffer[8192];
    
// open ssl socket read data
received = SSL_read (ssl, buffer, readSize);

// clear rubbish in socket
if (buffer[received-1] == '\n') buffer[received-1] = '\0';
// use buffer
json1 = std::string(buffer);
// cut < and >        
// json1 = replaceAll(json1, "<", "");
std::cout << json1 << endl;
// json1 = replaceAll(json1, ">", "");        
std::cout << json1 << endl;
json1 = replaceAll(json1, "\r", "");
std::cout << json1 << endl;
json1 = replaceAll(json1, "\n", "");
std::cout << json1 << endl;
json1 = replaceAll(json1, " ", "");
std::cout << json1 << endl;
// clear buffer
strcpy(buffer, "");
