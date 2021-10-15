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
#ifndef _CIBER_NETIF_
#define _CIBER_NETIF_

/* netif.h */

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

#endif
