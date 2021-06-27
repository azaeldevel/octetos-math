#ifndef OCTETOS_MATH_STATICS_HH
#define OCTETOS_MATH_STATICS_HH

#include <list>
#include <octetos/core/Exception.hh>

#include "core.hh"

namespace oct::math
{



template<typename T>
class Dataset : public std::list<T>
{
public:
	void add(T e)
	{
		std::list<T>::push_back(e);
	};
	
private:
	bool cmpDesc(const T f, const T s)
	{
		return f > s;
	}
};

}

#endif