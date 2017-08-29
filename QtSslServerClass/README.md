## C++ ssl socket server multiple clients fork() in separate files
### Install openssl
/*
 * Install:
 *  apt-get install openssl libssl-dev
 *
 * Add to .pro:
 *  LIBS += -lssl -lcrypto
 *
 */
### Add library to compile path when complie
SOURCES += main.cpp breakermindsslserver.cpp
<br>HEADERS += breakermindsslserver.h
<br>LIBS += -lssl -lcrypto
