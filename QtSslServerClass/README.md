## C++ ssl socket server multiple clients fork() in separate files
### Install openssl
apt-get install openssl libssl-dev

### Add to .pro:
LIBS += -lssl -lcrypto
 
### Add library to compile path when complie
SOURCES += main.cpp breakermindsslserver.cpp
<br>HEADERS += breakermindsslserver.h
<br>LIBS += -lssl -lcrypto

### Install mysql (you don't need for run server)
apt-get install libmysql++ libmysql++-dev libmysql+=-doc

### or use C mysql connector
https://github.com/breakermind/CppLinux/tree/master/MySqlConnector
