# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.50)
AC_INIT(shotgun, 1.0.0, songyancui@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

AC_ARG_ENABLE(debug,
              AS_HELP_STRING([--enable-debug], [enable debugging, default: yes]),
              [case "${enableval}" in
               yes) debug=1 ;;
               no)  debug=0 ;;
               *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
               esac],
               [debug=1])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"1")

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_INSTALL
AC_PREFIX_DEFAULT(/home/csy/dev/shotgun)

# remove default cflags '-g -o2'
CFLAGS=""
LDFLAGS="$LDFLAGS"
LIB_DIRS="/usr/local/lib $LIB_DIRS"

# Checks for libraries.

AC_CHECK_HEADER([event2/event.h],
                ,
                [AC_MSG_ERROR([libevent2 header not found - remember to install the development package too])]
                )
AC_CHECK_HEADER([event2/http.h],
                ,
                [AC_MSG_ERROR([libevent2 http header not found - remember to install the development package too])]
                )
AC_CHECK_HEADER([event2/buffer.h],
                ,
                [AC_MSG_ERROR([libevent2 buffer header not found - remember to install the development package too])]
                )

AC_CHECK_LIB([rt], [clock_gettime])

AC_CHECK_LIB(socket,
             bind,
             SOCKET_LIBS=-lsocket
             )

AC_CHECK_LIB([pthread],
             [pthread_create]
             )

AC_CHECK_LIB(event,
             event_base_new,
             [LIBS="-L /usr/local/lib -levent $LIBS"],
             [AC_MSG_ERROR([libevent2 not found])]
             )

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h limits.h stdlib.h string.h sys/time.h unistd.h])
AC_CHECK_HEADERS(fcntl.h limits.h strings.h syslog.h unistd.h [sys/cdefs.h] [sys/param.h] stdarg.h)
AC_CHECK_HEADER(inttypes.h,[AC_DEFINE([JSON_C_HAVE_INTTYPES_H],[1],[Public define for json_inttypes.h])])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_FORK
AC_TYPE_SIGNAL
AC_CHECK_FUNCS([socket])

AC_CHECK_FUNCS(strcasecmp strdup strndup strerror snprintf vsnprintf vasprintf open strncasecmp)

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
