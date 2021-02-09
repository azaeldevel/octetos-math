
#ifndef OCTETOS_MATH_CORE_HH
#define OCTETOS_MATH_CORE_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>
#include <cmath>

#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_INTEGER long
#define OCTETOS_MATH_EPSILON 0.0001

namespace metry::core
{
	template<class T>
	class Point : public std::vector<T>
	{
	public:
		Point() : std::vector<T>()
		{
		}
		Point(int dimension) : std::vector<T>(dimension)
		{
		}
	};
} 


#endif