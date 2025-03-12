QT += core gui widgets

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += main.cpp

INCLUDEPATH += /usr/include/yaml-cpp

LIBS += -lyaml-cpp
