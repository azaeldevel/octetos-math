

AC_INIT(octetos-math, 0.8.0-alpha, azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
dnl IT_PROG_INTLTOOL([0.35.0])

dnl GETTEXT_PACKAGE=math
dnl AC_SUBST(GETTEXT_PACKAGE)
dnl AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
dnl AM_GLIB_GNU_GETTEXT

LT_INIT

PKG_CHECK_MODULES(OCTETOS_CORE,octetos-core)

AM_CONDITIONAL(WITH_TESTS, test x"$with_tests" = "xyes")
AC_ARG_WITH([tests], AS_HELP_STRING([--with-tests], [Compilando con soporte para Tests]))
if test "x$with_tests" = "xyes"; then 
	PKG_CHECK_MODULES(CUNIT,cunit)
fi

AM_CONDITIONAL(WITH_3D, test x"$with_3d" = "xyes")
AC_ARG_WITH([3d], AS_HELP_STRING([--with-3d], [Compilando con soporte para 3D]))


AC_OUTPUT([
Makefile
src/Makefile
tests/Makefile
src/octetos-math.pc
])
