TEMPLATE = app

DEPENDPATH += $$PWD/../libRobSock
INCLUDEPATH += $$PWD/../libRobSock
CONFIG += release

win32 {
    DEFINES += MicWindows
    CONFIG(release, debug|release): LIBS += -L$$PWD/../libRobSock/release/ -lRobSock
    CONFIG(debug, debug|release): LIBS += -L$$PWD/../libRobSock/debug/ -lRobSock
}

symbian {
    LIBS += -lRobSock
}

unix {
    LIBS += -Wl,-rpath=$$PWD/../libRobSock/ -L$$PWD/../libRobSock/ -lRobSock
}

# Input
HEADERS += robfunc.h
SOURCES += mainRob.c robfunc.c
