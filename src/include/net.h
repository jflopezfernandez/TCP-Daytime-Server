
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

#include "config.h"

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
#endif

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

#ifndef SHUT_RD
#define SHUT_RD    0
#define SHUT_WR    1
#define SHUT_RDWR  2
#endif

/** Note:
 *
 *  The max length of an IPv4 address is 16 bytes:
 *  xxx.xxx.xxx.xxx + the null terminator.
 *
 */

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16
#endif

/** Note:
 *
 *  The max length of an IPv6 address is 46 bytes:
 *  xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx, or
 *  xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\0
 *
 */

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

#ifndef HAVE_BZERO
#define bzero(ptr,n) memset(ptr, 0, n)
#endif

#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host,family) gethostbyname((host))
#endif

/** The structure returned by recvfrom_flags():
 *  1. Destination IPv4 address
 *  2. Received interface index
 *
 */

struct unp_in_pkt_info {
    struct in_addr ipi_addr;
    int ipi_ifindex;
};

/** We need the newer CMSG_LEN() and CMSG_SPACE() macros, but few implementations support them today. These two macros
 *  really need an ALIGN() macro, but each implementation does this differently.
 *
 */

#ifndef CMSG_LEN
#define CMSG_LEN(size) (sizeof(struct cmsghdr) + (size))
#endif

#ifndef CMSG_SPACE
#define CMSG_SPACE(size) (sizeof(struct cmsghdr) + (size))
#endif

/** POSIX requires the SUN_LEN() macro, but not all implementations define it (yet). Note that this 4.4 BSD macro works
 *  regardless of whether there is a length field or not.
 *
 */

#ifndef SUN_LEN
#define SUN_LEN(su) (sizeof (*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif

/** POSIX renames "Unix domain as "local IPC." Not all systems define AF_LOCAL and PF_LOCAL (yet).
 *
 */

#ifndef AF_LOCAL
#define AF_LOCAL AF_UNIX
#endif

#ifndef PF_LOCAL
#define PF_LOCAL PF_UNIX
#endif

/** Infinite Poll Timeout
 *
 *  POSIX requires that an #include of <poll.h> define INFTIM, but many systems still define it in <sys/stropts.h>. We
 *  don't want to include all the STREAMS stuff if it's not needed, so we just define INFTIM here. This is the standard
 *  value, but there's no guarantee it's -1.
 *
 */

#ifndef INFTIM
#define INFTIM (-1)
#ifdef HAVE_POLL_H_
#define INFTIM_UNPH
#endif
#endif

/** Maximum Socket Connections
 *
 *  The following could be derived from SOMAXCONN in <sys/socket.h>, but many kernels still define it as 5, while
 *  actually supporting many more.
 *
 *  This will be the second argument to listen().
 *
 */

#define LISTENQ 1024

/** Miscellaneous Constants:
 *
 *  MAXLINE - Maximum text line length
 *  BUFFSIZE - Buffer size for reads and writes
 *
 */

#define MAXLINES 4096
#define BUFFSIZE 8192

/** Default Port Settings
 *
 *  SERV_PORT - Default server port
 *  SERV_PORT_STR - Default server port string
 *  UNIXSTR_PATH - "/tmp/unix.str" Unix domain stream
 *  UNIXDG_PATH - "/tmp/unix.dg" Unix domain datagram
 *
 */

/** The following shortens all the typecasts of pointer arguments:
 *
 */

#define SA struct sockaddr

/** RFC-3493: Protocol-independent placeholder for socket addresses
 *
 */

#define __SS_MAXSIZE 128
#define __SS_ALIGNSIZE (sizeof(int64_t))
#ifdef HAVE_SOCKADDR_SA_LEN
#define __SS_PAD1SIZE (__SS_ALIGNSIZE - sizeof(u_char) - sizeof(sa_family_t))
#else
#define __SS_PAD1SIZE (__SS_ALIGNSIZE - sizeof(sa_family_t))
#endif
#define __SS_PAD2SIZE (__SS_MAXSIZE - 2 * __SS_ALIGNSIZE)

struct sockaddr_storage {
#ifdef HAVE_SOCKADDR_SA_LEN
    u_char ss_len;
#endif
    sa_family_t ss_family;
    char __ss_pad1[__SS_PAD1SIZE];
    int64_t __ss_align;
    char __ss_pad2[__SS_PAD2SIZE];
};
#endif

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int);

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#ifndef HAVE_ADDRINFO_STRUCT
#include "../lib/addrinfo.h"
#endif

#ifndef HAVE_IF_NAMEINDEX_STRUCT
struct if_nameindex {
    unsigned int if_index;
    char *if_name;
};
#endif

#ifndef HAVE_TIMESPEC_STRUCT
struct timespec {
    time_t tv_sec;
    long tv_nsec;
};
#endif

#endif // SRC_INCLUDES_NET_H_

