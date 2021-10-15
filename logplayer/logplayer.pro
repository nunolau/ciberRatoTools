TEMPLATE	= app
CONFIG		+= qt warn_on release thread

win32 {
    DEFINES     += MicWindows
}

HEADERS		= cbbeacon.h cbclient.h\
                  cbgrid.h cbgridhandler.h cblab.h cblabhandler.h\
                  cbparameters.h cbparamhandler.h\
                  cbpoint.h cbposition.h cbreceptionform.h cbreceptionhandler.h\
                  cbreceptionist.h\
                  cblogplayer.h cbrobot.h cbtarget.h cbview.h cbviewcommand.h\
                  cbviewhandler.h cbwall.h\
		  cbloghandler.h
SOURCES		= cbbeacon.cpp cbclient.cpp\
                  cbgrid.cpp cbgridhandler.cpp cblab.cpp cblabhandler.cpp\
                  cbparameters.cpp cbparamhandler.cpp\
                  cbpoint.cpp cbposition.cpp cbreceptionhandler.cpp cbreceptionist.cpp\
                  cblogplayer.cpp cbrobot.cpp cbtarget.cpp cbview.cpp cbviewhandler.cpp\
                  cbwall.cpp cbloghandler.cpp logplayer.cpp

TARGET		= logplayer

QT              += xml network

FORMS           += logplayerGUI.ui


