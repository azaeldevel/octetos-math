
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = tests


tests_LDADD = $(top_builddir)/src/liboctetos-math.la
tests_CFLAGS = -I$(top_srcdir)/src
tests_SOURCES = main.cc
