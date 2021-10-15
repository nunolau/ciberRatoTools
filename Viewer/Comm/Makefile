QTDIR=/usr/lib/qt3
 
CXXFLAGS = -I $(QTDIR)/include -Wall -O3 -pipe -Wno-deprecated -DDEBUG
 
LIB = $(QTDIR)/lib
 
MOC = $(QTDIR)/bin/moc

OBJS =crqcomm.o crqreplyhandler.o\
	 crqcommhandler.o crqcontrolpanel.o crqcontrolpanel-moc.o\
     crqcomm-moc.o

libComm.a:	all
	ar -r libComm.a $(OBJS)

all: $(OBJS)

crqcontrolpanel-moc.cpp:	crqcontrolpanel.h
		$(MOC) crqcontrolpanel.h > crqcontrolpanel-moc.cpp

crqcomm-moc.cpp:	crqcomm.h
		$(MOC) crqcomm.h > crqcomm-moc.cpp
		
clean:
	 rm -f *.o 
	 rm -f *.a 
	 rm -f *-moc.cpp
	 rm -f *~
