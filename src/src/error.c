
#include "error.h"

int daemon_proc;

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap);

void
err_ret(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);

    return;
}

void
err_dump(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    abort();
}

void
err_msg(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, LOG_INFO, fmt, ap);
    va_end(ap);

    return;
}

void
err_quit(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

static void
err_doit(int errnoflag, int level, const char *fmt, va_list ap) {
    int errno_save, n;
    char buf[MAXLINES + 1];

    errno_save = errno;

#ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXLINES, fmt, ap);
#endif

    n = strlen(buf);

    if (errnoflag)
        snprintf(buf + n, MAXLINES - n, ": %s", strerror(errno_save));

    strcat(buf, "\n");

    if (daemon_proc) {
        syslog(level, buf);
    } else {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }

    return;
}
