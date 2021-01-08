
AUTOMAKE_OPTIONS=foreign 1.4

OCTETOS_MATH_DEFINES = 
if WITH_TESTS
OCTETOS_MATH_DEFINES += -DDEBUG -g -O0
endif
if WITH_3D
OCTETOS_MATH_DEFINES += -DOCTETOS_MATH_DIMENSION=3
else
OCTETOS_MATH_DEFINES += -DOCTETOS_MATH_DIMENSION=2
endif

lib_LTLIBRARIES = liboctetos-math.la

liboctetos_math_la_SOURCES = metry.cc
liboctetos_math_la_LIBADD = $(OCTETOS_CORE_LIBS)
liboctetos_math_la_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_MATH_DEFINES)

octetos_math_includedir = $(includedir)/octetos/math
octetos_math_include_HEADERS = metry.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-math.pc

EXTRA_DIST = octetos-math.pc.in