## C++ ssl socket server multiple clients fork() in separate files

### Add library to compile path when complie
SOURCES += main.cpp breakermindsslserver.cpp
HEADERS += breakermindsslserver.h
LIBS += -lssl -lcrypto
