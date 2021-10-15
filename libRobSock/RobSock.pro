TARGET = RobSock
TEMPLATE = lib
CONFIG   += dynamiclib release
DEFINES  += CIBERQTAPP ROBSOCK_LIBRARY
INCLUDEPATH += .

win32 {
    DEFINES += MicWindows
    LIBS += -lws2_32
}

# Input
HEADERS += cmeasures.h \
           croblink.h \
           csimparam.h \
           netif.h \
           RobSock.h \
           structureparser.h
SOURCES += cmeasures.cpp \
           croblink.cpp \
           csimparam.cpp \
           netif.cpp \
           RobSock.cpp \
           structureparser.cpp

QT += xml
