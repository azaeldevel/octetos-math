
AUTOMAKE_OPTIONS=foreign 1.4

OCTETOS_MATH_DEFINES = 
if WITH_TESTS
OCTETOS_MATH_DEFINES += -D DEBUG -g -O0 
endif


lib_LTLIBRARIES = liboctetos-math.la

liboctetos_math_la_SOURCES = core.cc metry.cc Prime.cc
liboctetos_math_la_LIBADD = $(OCTETOS_CORE_LIBS)
liboctetos_math_la_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) 

octetos_math_includedir = $(includedir)/octetos/math
octetos_math_include_HEADERS = core.hh Point.hh Vector.hh defines.hh matrix.hh statics.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-math.pc

EXTRA_DIST = octetos-math.pc.in