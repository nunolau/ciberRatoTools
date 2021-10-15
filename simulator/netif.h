/*
    This file is part of ciberRatoToolsSrc.

    Copyright (C) 2001-2011 Universidade de Aveiro

    ciberRatoToolsSrc is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ciberRatoToolsSrc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/* netif.h */

/* $Id: netif.h,v 1.1 2007-09-26 08:38:23 nuno Exp $ */

#ifndef MicWindows

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#else

#include <WinSock2.h>

#endif


#define ROB_INFO 1
#define WALL_INFO 2
#define CIRC_INFO 3

#define ROB_INIT   1
#define ROB_STATUS 2
#define ROB_DEL    3

#define START_COMM        1
#define STOP_COMM         2
#define NEWROBOT_COMM    10
#define VIEWER_COMM      15
#define LABREQ_COMM      20
#define OK_COMM          25   // reply from server after robot registering
                              // can be used to indicate robot position
#define DEL1_COMM      30
#define DEL2_COMM      31
#define DEL3_COMM      32

typedef struct {
           unsigned short mode;
           unsigned short time;
	   union {
               struct {
	          unsigned short rob,type;
		  union {
                     struct {
                        unsigned short x,y,dir,score;
		     } st;
		     char init[20];
		  } u;
	       } rob_info;
               struct {
                    unsigned short xi,yi,xf,yf;
	       } wall_info;
               struct {
                    unsigned short x,y,r;
	       } circ_info;
	   } u;
	 } ViewMessage;
	 
typedef struct {
           unsigned short lPow;
           unsigned short rPow;
           unsigned short end;
	 } ActMessage;

typedef struct {
           unsigned short comm;
	   union {
	        char rob_name[20];
		struct {
		    unsigned short cycle_time;
		    unsigned short sim_time_final;
		    unsigned short noise_obstacles;
		    unsigned short noise_beacon;
		    unsigned short noise_compass;
		    unsigned short noise_motors;
	        } params;
	   }u;
	 } CommMessage;

typedef struct {
           unsigned short time;
           unsigned short left,right,center;
           unsigned short light;
           unsigned short compass;
           unsigned short ground;
           unsigned short collision;
           unsigned short start;
           unsigned short stop;
	   unsigned short endLed;
	 } SenseMessage;
	 
class Port {
	public: 

		Port() ;			
		Port(int lPort) ;			
		Port(int port,char *RemoteHost, int lPort=0) ;			
		~Port() ;			
		bool		init(bool blocking=1) ;	
		bool		send_info(void *buf,int bufSize) ;
		int		recv_info(void *buf, int bufSize) ;
		sockaddr_in     GetLastSender(void);
		void            SetRemote(sockaddr_in rem_addr);

		int		socketfd ;			/* socket discriptor */
        private:
		bool		init_local(void) ;	
		bool		init_remote(void) ;	
		struct sockaddr_in	remote_addr ;		/* remote addr structure */
		struct sockaddr_in	lastsender_addr ;	/* sender of last received message addr structure */
		char		host[256] ;			/* remote host name */
		int		portnum ;			/* remote port number */
		int		localport ;			/* local port number */
} ;
