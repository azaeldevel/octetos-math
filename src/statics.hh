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
	Dataset()
	{
		sorted = true;
	};
	void add(T e)
	{
		std::list<T>::push_back(e);
	};
	
	unsigned int getCounter()const
	{
		return std::list<T>::size();
	}
	T getMax() const
	{
		return *std::list<T>::begin();
	}
	T getMin() const
	{
		return *(--std::list<T>::end());
	}
	bool getSorted()const
	{
		return sorted;
	}

	void sort()
	{
		std::list<T>::sort(cmpDesc);
		sorted = true;
	};
private:
	static bool cmpDesc(const T f, const T s)
	{
		return f > s;
	}

private:
	bool sorted;
};

}

#endif