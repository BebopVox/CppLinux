QT += core
QT -= gui

TARGET = BreakermindServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    breakermindsslserver.cpp

HEADERS += \
    breakermindsslserver.h

LIBS += -lssl -lcrypto
