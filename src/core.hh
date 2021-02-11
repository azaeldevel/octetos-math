
#ifndef OCTETOS_MATH_CORE_HH
#define OCTETOS_MATH_CORE_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>
#include <cmath>

#include "defines.hh"

namespace metry
{
	typedef OCTETOS_MATH_DECIMAL decimal;
	typedef OCTETOS_MATH_INTEGER integer;

	static decimal epsilon = OCTETOS_MATH_EPSILON;

	namespace core
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
	
} 


#endif