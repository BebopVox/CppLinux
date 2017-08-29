## C++ ssl socket server multiple clients fork() in separate files

### Add library to compile path when complie
SOURCES += main.cpp \
<br>    breakermindsslserver.cpp
<br>
HEADERS += \
<br>    breakermindsslserver.h
<br>    
LIBS += -lssl -lcrypto
