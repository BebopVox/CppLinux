## Ssl socket server openssl multiple connections

Update sources and install first 
apt-get update

// g++
apt-get install g++ bulid-essential

//  open ssl
apt-get install openssl libssl-dev 

// mysql (don't need here)
apt-get install libmysql++ libmysql++-dev libmysql++-doc

Compile with: 
g++ -o server server.cpp -lssl -lcrypto

Connect:
openssl s_client -connect 127.0.0.1:3333
telnet-ssl -z ssl 127.0.0.1 3333
