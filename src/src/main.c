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

#include "error.h"
#include "net.h"

// TODO: Continue with main.c (pg. 6)

int main(int argc, char *argv[])
{
	int sockfd, n;
	char recvline[MAXLINES + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: echo <IPaddress>");

	sockfd = createSocket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("Connection error");

	while ((n = read(sockfd, recvline, MAXLINES)) > 0) {
		recvline[n] = 0;

		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}

	if (n < 0)
		err_sys("Read error");

	return EXIT_SUCCESS;
}

