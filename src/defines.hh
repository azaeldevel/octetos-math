
#ifndef OCTETOS_MATH_DEFINES_HH
#define OCTETOS_MATH_DEFINES_HH

#if defined(__GNUC__) && defined(__linux__)
    #include <octetos/core/defines.hh>
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))
    #include <defines.hh>
#else
    #error "Pltaforma desconocida"
#endif


#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_INTEGER long
#define OCTETOS_MATH_EPSILON 0.0001
#define EPSILON 1.0e-29

#endif
