/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main echo server implementation file
 *
 *        Version:  1.0
 *        Created:  06/07/2018 09:28:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Fernando Lopez Fernandez 
 *   Organization:  Southern New Hampshire University
 *
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "error.h"
#include "net.h"

#ifdef _WIN32
#define AF_INET 2
#define SOCK_STREAM 1
#define INADDR_ANY ((unsigned long int) 0x00000000)
#define htons(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#define htonl(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))
#endif

// TODO: Continue with main.c (pg. 6)

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char recvline[MAXLINES + 1];
	time_t ticks;

	listenfd = createSocket(AF_INET, SOCK_STREAM, NULL);

	memset(&servaddr, 0, sizeof (servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);

	BindToSocket(listenfd, (SocketAddress *) &servaddr, sizeof (servaddr));
	ListenForConnections(listenfd, LISTENQ);

	return EXIT_SUCCESS;
}

