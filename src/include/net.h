
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

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/wait.h>

#include <unistd.h>

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

#define SERV_PORT 9877
#define SERV_PORT_STR "9877"
#define UNIXSTR_PATH "/tmp/unix.str"
#define UNIXDG_PATH "/tmp/unix.dg"

/** The following shortens all the typecasts of pointer arguments:
 *
 */

#define SocketAddress struct sockaddr*

#ifndef HAVE_STRUCT_SOCKADDR_STORAGE

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

/** @fn int createSocket(int domain, int type, int protocol)
 *
 *  Original function: socket()
 *
 *  @param family
 *  @param type
 *  @param protocol
 *
 *  @details Creates an endpoint for communication and returns a file descriptor
 *  that refers to that endpoint. The file descriptor returned by a successful
 *  call will be the lowest-numbered file descriptor not currently opened for
 *  the process.
 *
 *  The domain argument specifies a communication domain; this selects the
 *  protocol  family which will be used for communication. These families are
 *  defined in <sys/socket.h>. The currently understood formats are:
 *
 *  AF_UNIX, AF_LOCAL   Local communication
 *  AF_INET             IPv4 Internet Protocols
 *  AF_INET6            IPv6 Internet Protocols
 *  AF_PACKET           Low-level packet interface
 *  AF_ALG              Interface to kernel crypto API
 *
 *  The socket has the indicated type, which specifies the communication
 *  semantics. Currently defined types are:
 *
 *  SOCK_STREAM         Provides sequenced, reliable, two-way connection-based
 *                      byte streams. An out-of-band data transmission
 *                      mechanism may be supported.
 *
 *  SOCK_DGRAM          Supports datagrams (connectionless, unreliable messages
 *                      of a fixed maximum length).
 *
 *  SOCK_SEQPACKET      Provides a sequenced, reliable, two-way connection-based
 *                      data transmission path for datagrams of fixed maximum
 *                      length; a consumer is required to read an entire packet
 *                      with each input system call.
 *
 *  SOCK_RAW            Provides raw network protocol access.
 *
 *  SOCK_RDM            Provides a reliable datagram layer that does not
 *                      guarantee ordering.
 *
 *  SOCK_PACKET         Obsolete and should not be used in new programs.
 *
 *  Since Linux 2.6.27, the type argument serves a second purpose: in addition
 *  to specifying a socket type, it may include the bitwise OR of any of the
 *  following values, to modify the behavior of socket():
 *
 *  SOCK_NONBLOCK       Set the O_NONBLOCK file status flag on the new open
 *                      file descriptor. Using this flag saves extra calls to
 *                      fcntl(2) to achieve the same result.
 *
 *  SOCK_CLOEXEC        Set the close-on-exec (FD_CLOEXEC) flag on the new file
 *                      descriptor. See the description of the O_CLOEXEC flag
 *                      in open(2) for reasons why this may be useful.
 *
 *  @returns int
 *
 */

int
createSocket(int family, int type, int protocol);

int
connectSocket(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int readSocketStream();

#endif // SRC_INCLUDES_NET_H_

