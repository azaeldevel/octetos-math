

bin_PROGRAMS = tests


tests_LDADD = $(top_builddir)/src/liboctetos-math.la $(CUNIT_LIBS)  $(OCTETOS_CORE_LIBS)
tests_CXXFLAGS = -I$(top_srcdir)/src $(CUNIT_CFLAGS) $(OCTETOS_CORE_CFLAGS)
tests_SOURCES = main.cc sta-ops.cc
