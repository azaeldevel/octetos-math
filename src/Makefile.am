AUTOMAKE_OPTIONS=foreign 1.4

lib_LTLIBRARIES = liboctetos-math.la

OCTETOS_MATH_DEFINES = 
if WITH_TESTS
OCTETOS_MATH_DEFINES += -DDEBUG
endif

liboctetos_math_la_SOURCES = metry.cc
liboctetos_math_la_LIBADD = $(OCTETOS_CORE_LIBS)
liboctetos_math_la_CFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_MATH_DEFINES)
