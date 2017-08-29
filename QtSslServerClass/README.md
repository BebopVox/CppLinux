## C++ ssl socket server multiple clients fork() in separate files

### Add library to compile path when complie
SOURCES += main.cpp breakermindsslserver.cpp
<br>HEADERS += breakermindsslserver.h
<br>LIBS += -lssl -lcrypto
