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
// clear buffer
strcpy(buffer, "");
