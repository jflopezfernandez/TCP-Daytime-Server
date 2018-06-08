/*
 * =============================================================================
 *
 *       Filename:  net.h
 *
 *    Description:  Main network include file
 *
 *        Version:  1.0
 *        Created:  06/07/2018 09:32:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Fernando Lopez Fernandez
 *   Organization:  Southern New Hampshire University
 *
 * =============================================================================
 */

#ifndef SRC_INCLUDES_NET_H_
#define SRC_INCLUDES_NET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>

#ifdef HAVE_SYS_SELECT_H_
#include <sys/select.h>
#endif

#ifdef HAVE_SYS_SYSCTL_H_
#include <sys/sysctl.h>
#endif

#ifdef HAVE_POLL_H_
#include <poll.h>
#endif

#ifdef HAVE_SYS_EVENT_H_
#include <sys/event.h>
#endif

#ifdef HAVE_STRING_H_
#include <string.h>
#endif

/** Socket Programming Interface:
 *
 *  The three headers generally needed for socket or file IO control are 
 *  IO Control (ioctl), File IO (filio), and Socket IO (sockio), included
 *  here.
 *
 */

#ifdef HAVE_SYS_IOCTL_H_
#include <sys/ioctl.h>
#endif

#ifdef HAVE_FILIO_H_
#include <sys/filio.h>
#endif

#ifdef HAVE_SYS_FILIO_H_
#include <sys/sockio.h>
#endif

#ifdef HAVE_PTHREAD_H_
#include <pthread.h>
#endif

#ifdef HAVE_NET_IF_DL_H_
#include <net/if_dl.h>
#endif

#ifdef HAVE_NET_IF_DL_H_
#include <netinet/sctp.h>
#endif

/** Note:
 *
 *  OSF/1 actually disables recv() and send() in <sys/socket.h>, so we must
 *  redefine them as follows:
 *
 */

#ifdef __osf__
#undef recv
#undef send

#define recv(a,b,c,d) recvfrom(a,b,c,d)
#define send(a,b,c,d) sendto  (a,b,c,d)

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

#ifndef SHUT_RD
#define SHUT_RD    0
#define SHUT_WR    1
#define SHUT_RDWR  2
#endif

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16
#endif

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

#ifndef HAVE_BZERO
#define bzero(ptr,n) memset(ptr, 0, n)
#endif

#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host,family) gethostbyname((host))
#undef

// TODO: Continue here (pg. 901)

#endif // SRC_INCLUDES_NET_H_

