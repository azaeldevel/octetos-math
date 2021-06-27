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
	
	unsigned int counter()const
	{
		return std::list<T>::size();
	}
	T max() const
	{
		if(not sorted) throw octetos::core::Exception("El conjunto de datos no esta ordenado");
		return *std::list<T>::begin();
	}
	T min() const
	{
		if(not sorted) throw octetos::core::Exception("El conjunto de datos no esta ordenado");
		return *(--std::list<T>::end());
	}
	bool getSorted()const
	{
		return sorted;
	}	

	T range() const
	{
		return max()-min();
	}	
	unsigned int categories()const
	{
		return round(1 + (3.3 * log10(counter())));
	}
	unsigned int amplitude()const
	{
		return range()/categories();
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