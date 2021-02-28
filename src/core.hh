
#ifndef OCTETOS_MATH_CORE_HH
#define OCTETOS_MATH_CORE_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>
#include <cmath>

#include "defines.hh"

namespace math
{
	typedef OCTETOS_MATH_DECIMAL decimal;
	typedef OCTETOS_MATH_INTEGER integer;

	static decimal epsilon = OCTETOS_MATH_EPSILON;

	class Exception : public octetos::core::Exception
	{
	public:
		Exception(const std::string& msg,const char* fn,int line);
		Exception(const std::string& msg);
	};
	
	/*template<class T>
	class Array : public std::vector<T>
	{
	public:
		Array() : std::vector<T>()
		{
		}
		Array(int dimension) : std::vector<T>(dimension)
		{
		}
	};*/
	
	template<class T>
	class Sets : public std::vector<T>
	{
	public:
		
		//
		const Sets& operator || (const Sets&);//union
		const Sets& operator && (const Sets&);//interseccion
	};
} 



#endif