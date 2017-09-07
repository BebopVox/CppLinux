QT += core network
QT -= gui

TARGET = iThreads
CONFIG += console
CONFIG -= app_bundle

// C++ compile with -lssl -lcrypto -std=c++11
LIBS += -lpthread -lssl -lcrypto -lresolv -std=c++11

TEMPLATE = app

SOURCES += main.cpp \
    breakermindsslserver.cpp

HEADERS += \
    breakermindsslserver.h
