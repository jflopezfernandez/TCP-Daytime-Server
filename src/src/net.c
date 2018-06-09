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

int connectSocket(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	int status = NULL;

	if ((n = connect(sockfd, addr, addrlen)) < 0) {
		err_sys("Connection error");
	}

	return status;
}

int readSocketStream() {
	err_sys("TODO: Implement function (readSocketStream)");

	exit(EXIT_FAILURE);

	return -1;
}
