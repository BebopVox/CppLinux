## Ssl socket server openssl multiple connections

<br> Update sources and install first <br>
apt-get update

<br> g++ <br>
apt-get install g++ bulid-essential

<br> open ssl <br>
apt-get install openssl libssl-dev 

<br> mysql (don't need here) <br>
apt-get install libmysql++ libmysql++-dev libmysql++-doc

<br> Compile with: <br>
g++ -o server serverSsl.cpp -lssl -lcrypto 

<br> Connect:<br>
openssl s_client -connect 127.0.0.1:3333 <br>
telnet-ssl -z ssl 127.0.0.1 3333 <br>

