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
/* netif.cpp */


#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <string.h>

#ifndef MicWindows

#include <unistd.h>

#endif

#include "netif.h"

#define DEFAULT_PORT_NUMBER 6001

Port::Port()
{
#ifdef MicWindows
    WORD wVersionRequested;
	WSADATA wsaData; 
	 
	wVersionRequested = MAKEWORD(1, 1); 
 
	WSAStartup(wVersionRequested, &wsaData);
#endif
	strcpy(host, "") ;
	localport=0;
}

Port::Port(int lPort)
{
#ifdef MicWindows
    WORD wVersionRequested;
	WSADATA wsaData; 
	 
	wVersionRequested = MAKEWORD(1, 1); 
 
	WSAStartup(wVersionRequested, &wsaData);
#endif
	strcpy(host, "") ;
	localport=lPort;
}

/**
 * RemoteHost may be in the form host:hostport in which case
 * hostport takes predecence over port
 */
Port::Port(int port, char *RemoteHost,int lPort)
{
	char hostaux[2048];
	int porthost;
#ifdef MicWindows
    WORD wVersionRequested;
	WSADATA wsaData; 
	 
	wVersionRequested = MAKEWORD(1, 1); 
 
	WSAStartup(wVersionRequested, &wsaData);
#endif
	if(sscanf(RemoteHost,"%2047[^:]:%d",hostaux,&porthost) == 2) {
	    strncpy(host, hostaux,255) ;
	    host[255]='\0';
	    portnum = porthost ;
	    localport=lPort;
	}
	else {
	    strncpy(host, RemoteHost,255) ;
	    host[255]='\0';
	    portnum = port ;
	    localport=lPort;
	}
	//fprintf(stderr,"remote host = \"%s\" port = %d\n",host,portnum);
}

Port::~Port()
{
#ifndef MicWindows
    close(socketfd);
#else
    closesocket(socketfd);
#endif
}

sockaddr_in Port::GetLastSender(void)
{
     return lastsender_addr;
}

void Port::SetRemote(sockaddr_in rem_addr)
{
     remote_addr=rem_addr;
}

bool Port::init_local(void)
{
	struct sockaddr_in	local_addr ;

	/* Open UDP socket */
	if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return false ;	/* Can't open socket. */

	/* Bind local address */
	memset((char *)&local_addr, 0, sizeof(local_addr)) ;
	local_addr.sin_family		= AF_INET ;
	local_addr.sin_addr.s_addr	= htonl(INADDR_ANY) ;
	local_addr.sin_port		= htons(localport) ;

	if (bind(socketfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0)
        return false ;

    return true;
}

bool Port::init_remote(void)
{
	struct hostent		*host_ent ;
	struct in_addr		*addr_ptr ;

	if ((host_ent = (struct hostent *)gethostbyname(host)) == NULL) {
		/* Check if a numeric address */
		if (inet_addr(host) == INADDR_NONE)
            return false ;
	}
	else{
		addr_ptr = (struct in_addr *) *host_ent->h_addr_list ;
		strcpy(host,inet_ntoa(*addr_ptr)) ;
	}

	/* Fill in the structure with the address of the remote UDP socket  */
	memset((char *) &remote_addr, 0, sizeof(remote_addr)) ;
	remote_addr.sin_family		= AF_INET ;
	remote_addr.sin_addr.s_addr	= inet_addr(host) ;
	remote_addr.sin_port		= htons(portnum) ;

    return true;
}

bool Port::init(bool blocking)
{
    if(!init_local()) return false;
	
    if(strcmp(host,"")!=0)
        if(!init_remote()) {

#ifndef MicWindows
            close(socketfd);
#else
            closesocket(socketfd);
#endif
            return false;
        }

    if(!blocking)
#ifndef MicWindows
        fcntl(socketfd,F_SETFL,O_NONBLOCK);
#else
    {
        u_long dummy;
        ioctlsocket(socketfd, FIONBIO, &dummy);
    }
#endif

    return true;
}

bool Port::send_info(void *buf, int bufSize)
{

//    fprintf(stderr,"Sending \"%.*s\"\n",bufSize,(char *)buf);

#ifndef MicWindows
    if (sendto(socketfd, buf, bufSize, 0,
		   (struct sockaddr *)&remote_addr, sizeof(remote_addr)) != bufSize)
#else
    if (sendto(socketfd, (const char *)buf, bufSize, 0,
		   (struct sockaddr *)&remote_addr, sizeof(remote_addr)) != bufSize)
#endif
        return false;

    return true;
}

int Port::recv_info(void *buf, int bufSize)
{
	int n;
	size_t  lastsenderlen ;

	lastsenderlen = sizeof(lastsender_addr) ;
#ifndef MicWindows
	n = recvfrom(socketfd, (char *)(buf), bufSize, 0,
		     (struct sockaddr *)&lastsender_addr, (socklen_t *) &lastsenderlen);
#else
	n = recvfrom(socketfd, (char *)(buf), bufSize, 0,
		     (struct sockaddr *)&lastsender_addr, (int *) &lastsenderlen);
#endif

	return n;
}
