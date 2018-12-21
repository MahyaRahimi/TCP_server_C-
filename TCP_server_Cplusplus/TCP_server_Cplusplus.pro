TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread

SOURCES += main.cpp \
    tcp.cpp \
    transmitter.cpp \
    listener.cpp

HEADERS += \
    tcp.h \
    transmitter.h \
    listener.h
