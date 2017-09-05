QT += core network
QT -= gui

TARGET = SslClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lssl -lcrypto -std=c++11 -L.

SOURCES += main.cpp

DISTFILES += \
    json-email-commands.txt
