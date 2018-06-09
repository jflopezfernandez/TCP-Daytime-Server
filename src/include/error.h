
/*
 * =============================================================================
 *
 *       Filename:  error.h
 *
 *    Description:  Main error-handling file.
 *
 *        Version:  1.0
 *        Created:  06/09/2018 07:02:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Fernando Lopez Fernandez
 *   Organization:  Southern New Hampshire University
 *
 * =============================================================================
 */

#ifndef TCP_DAYTIME_SERVER_ERROR_H
#define TCP_DAYTIME_SERVER_ERROR_H

#include <stdarg.h>
#include <string.h>
#include <syslog.h>

/** @fn void err_ret(const char *fmt, ...)
 *  @brief Nonfatal error related to system call.
 *  Just print the error message and return the code.
 *  @param Error message to print to STDERR
 *  @returns void
 *
 */

void
err_ret(const char *fmt, ...);

/** Fatal error related to a system call.
 *  Print the message, dump core, and terminate.
 *
 */

void
err_dump(const char *fmt, ...);

void
err_msg(const char *fmt, ...);

void
err_quit(const char *fmt, ...);



#endif //TCP_DAYTIME_SERVER_ERROR_H
