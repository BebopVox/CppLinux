# C++ smtp ssl socket client with attachments
Qt project

# About
How to get mx hosts for email addres from dns server and send email to all servers on different ports(25,587, no authentication needed).
<br>Example show how send email to first working smtp server.

# Install and compile
### apt-get install libssl-dev openssl
### g++ -o output main.cpp -lssl -lcrypto -lresolv -std=c++11
