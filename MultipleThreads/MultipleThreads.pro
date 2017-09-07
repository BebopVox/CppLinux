QT += core network
QT -= gui

TARGET = iThreads
CONFIG += console
CONFIG -= app_bundle

LIBS += -lpthread -std=c++11

TEMPLATE = app

SOURCES += main.cpp
