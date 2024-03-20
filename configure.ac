# configure.ac
AC_INIT([unittest3], [1.0], [your.email@example.com])
AM_INIT_AUTOMAKE

# Set default CFLAGS if not already set by the user.
AC_ARG_ENABLE(debug,
[AS_HELP_STRING([--enable-debug],[Enable debugging information and disable optimizations])],
[case "${enableval}" in
yes) CFLAGS="-O0 -g $CFLAGS" ;;
no) ;;
*) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[if test -z "$CFLAGS"; then
    CFLAGS="-O0 -g -fsanitize-address-use-after-scope -fsanitize=address -fno-omit-frame-pointer"
fi])

if test -z "$CC"; then
  AC_PATH_PROG(CC, clang)
fi

AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
