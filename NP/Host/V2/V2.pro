TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq -lws2_32 -lIphlpapi
INCLUDEPATH += D:\School\NP\include

SOURCES += \
        game.cpp \
        init.cpp \
        main.cpp

HEADERS += \
    game.h \
    init.h
