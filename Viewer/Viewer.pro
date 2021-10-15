TEMPLATE = app
CONFIG   += qt warn_off release thread
#CONFIG   += qt warn_on debug thread
DEPENDPATH += Lab

#DEFINES += DEBUG

win32 {
    DEFINES += MicWindows
    LIBS += -lws2_32
}

# Input
HEADERS += \
    crmainparameters.h \
    crqscene.h \
    crqparamhandler.h \
    Comm/crqcomm.h \
    crqrobotinfo.h \
    crqlabview.h \
    crqdataview.h
SOURCES += \
    crmainparameters.cpp \
    crqparamhandler.cpp \
    main.cpp \
    Lab/crbeacon.cpp \
    Lab/crgrid.cpp \
    Lab/crlab.cpp \
    Lab/crrobot.cpp \
    Lab/crtarget.cpp \
    Lab/crvertice.cpp \
    Lab/crwall.cpp \
    Comm/crqcomm.cpp \
    Comm/crqcommhandler.cpp \
    Comm/crqreplyhandler.cpp \
    crqrobotinfo.cpp \
    crqlabview.cpp \
    crqdataview.cpp \
    crqscene.cpp

QT += network xml

FORMS += \
    crqrobotinfo.ui \
    crqlabview.ui \
    crqdataview.ui

RESOURCES += \
    default.qrc
