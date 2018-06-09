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
	int n;

	if ((n = socket(family, type, protocol)) < 0) {
		err_sys("Socket error");
	}

	return (n);
}

