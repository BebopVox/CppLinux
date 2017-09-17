QT += core network
QT -= gui

TARGET = SslClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lssl -lcrypto -lresolv -std=c++11 -L.

SOURCES += main.cpp \
    sslclient.cpp \
    dnsrecords.cpp \
    sslsmtp.cpp

DISTFILES += \
    json-email-commands.txt

HEADERS += \
    sslclient.h \
    dnsrecords.h \
    sslsmtp.h

