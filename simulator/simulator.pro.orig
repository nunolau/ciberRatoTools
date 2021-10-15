TEMPLATE    = app
CONFIG      += qt warn_on release thread
#CONFIG      += qt warn_on debug thread

win32 {
        DEFINES += MicWindows
        LIBS    += -lws2_32
}

HEADERS = \
    cbactionhandler.h cbbeacon.h cbbutton.h cbclient.h\
    cbgrid.h cbgridhandler.h cblab.h cblabhandler.h\
    cbmotor.h cbpanel.h cbparameters.h cbparamhandler.h\
    cbpoint.h cbposition.h cbreceptionform.h cbreceptionhandler.h\
    cbreceptionist.h cbrobot.h cbrobotaction.h cbsensor.h\
    cbsimulator.h cbtarget.h cbview.h cbviewcommand.h\
    cbviewhandler.h cbwall.h cbgraph.h cbrobotbeacon.h\
    cbutils.h cbparamdialog.h cbsimulatorGUI.h cbcontrolpanel.h \
    cbmanagerobots.h \
    cbrobotinfo.h \
    cblabdialog.h

SOURCES = \
    cbactionhandler.cpp cbbeacon.cpp cbbutton.cpp cbclient.cpp\
    cbgrid.cpp cbgridhandler.cpp cblab.cpp cblabhandler.cpp\
    cbmotor.cpp cbpanel.cpp cbparameters.cpp cbparamhandler.cpp\
    cbpoint.cpp cbposition.cpp cbreceptionhandler.cpp cbreceptionist.cpp\
    cbrobot.cpp cbrobotaction.cpp cbsensor.cpp\
    cbsimulator.cpp cbtarget.cpp cbview.cpp cbviewhandler.cpp\
    cbwall.cpp simulator.cpp cbgraph.cpp cbrobotbeacon.cpp\
    cbutils.cpp cbparamdialog.cpp cbsimulatorGUI.cpp cbcontrolpanel.cpp \
    cbmanagerobots.cpp \
    cbrobotinfo.cpp \
    cblabdialog.cpp

TARGET  = simulator
QT      += network  xml

FORMS   += \
    cbsimulatorGUI.ui \
    cbcontrolpanel.ui \
    cbmanagerobots.ui \
    cbparamdialogbase.ui \
    cbrobotinfo.ui \
    cblabdialog.ui

RESOURCES   += \
    default.qrc
