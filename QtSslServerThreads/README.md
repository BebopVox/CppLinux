# C++ ssl server socket multiple threads(connections)

### Install
apt-get install openssl libssl-dev g++ bulid-essential

### Compile
g++ -lpthread -lssl -lcrypto -lresolv -std=c++11

### Ssl client
https://github.com/breakermind/CppLinux/blob/master/QtSslClient/main.cpp

### Threads
http://man7.org/linux/man-pages/man3/pthread_create.3.html
