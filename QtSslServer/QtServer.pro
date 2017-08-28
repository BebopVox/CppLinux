QT += core
QT -= gui

TARGET = QtServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

# How to add external library
# LIBS += -L/path/to -lpsapi
LIBS += -lssl -lcrypto
