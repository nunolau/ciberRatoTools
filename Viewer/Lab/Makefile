QTDIR=/usr/lib/qt3
 
CXXFLAGS = -I $(QTDIR)/include -Wall -O3 -pipe -Wno-deprecated
 
LIB = $(QTDIR)/lib

OBJS = crvertice.o crwall.o crbeacon.o crtarget.o crlab.o crgrid.o crrobot.o

libLab.a:	all
	ar -r libLab.a $(OBJS)

all: $(OBJS)

clean:
	 rm -f *.o 
	 rm -f *.a 
	 rm -f *~
