#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Buffer], [0.0], [paulkhomich@outlook.com])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([buf.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

define(DATE, `date`)dnl
define(SEDCOM, [\/\* COMMENT:: AC_PACKAGE_NAME, AC_PACKAGE_VERSION: DATE \*\/])dnl
define(SEDSTR, [1 s/^\/\* COMMENT::.*\*\//SEDCOM/; t; 1 s/^/SEDCOM\n/;])dnl
define(SEDOPT, ["SEDSTR"])dnl

sed -i -s SEDOPT *.{c,h}
