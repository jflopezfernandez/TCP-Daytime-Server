/*
 * =====================================================================================
 *
 *       Filename:  net.c
 *
 *    Description:  Net-related functions implementation file.
 *
 *        Version:  1.0
 *        Created:  06/09/2018 04:47:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Fernando Lopez Fernandez
 *   Organization:  Southern New Hampshire University
 *
 * =====================================================================================
 */

#include "net.h"

int
createSocket(int family, int type, int protocol) {
	int status = NULL;

	if ((status = socket(family, type, protocol)) < 0) {
		/** TODO: Test for specific error
		 *
		 *  EACCESS
		 *  EAFNOSUPPORT
		 *  EINVAL
		 *  EINVAL
		 *  EMFILE
		 *  ENFILE
		 *  ENOBUFS
		 *  EPROTONOSUPPORT
		 *
		 */

		err_sys("Socket error");
	}

	return status;
}

int connectSocket(int sockfd, const struct sockaddr *addr, size_t addrlen) {
	int status = NULL;

	if ((status = connect(sockfd, addr, addrlen)) < 0) {
		err_sys("Connection error");
	}

	return status;
}

// TODO: Implement readSocketStream()
int readSocketStream() {
	err_sys("TODO: Implement function (readSocketStream)");

	exit(EXIT_FAILURE);

	return -1;
}

int ListenForConnections(int socketfd, int backlog) {
	int status = NULL;

	if ((status = listen(socketfd, backlog)) < 0) {
		err_sys("Listen error");
	}

	return status;
}

int BindToSocket(int sockfd, const struct sockaddr *addr, size_t addrlen) {
	int status = NULL;

	if ((status = bind(sockfd, (SocketAddress) addr, addrlen)) < 0) {
		err_sys("Bind error");
	}

	return status;
}
