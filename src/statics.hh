#ifndef OCTETOS_MATH_STATICS_HH
#define OCTETOS_MATH_STATICS_HH

#include <list>
#include <octetos/core/Exception.hh>

#include "core.hh"

namespace oct::math
{

typedef unsigned int categorie;

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
	categorie categories()const
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


template<typename T>
struct Frecuency
{
	T min;
	T max;
	unsigned int frec;
};

template<typename T>
class FrecuencyTable : public std::list<Frecuency<T>>
{
public:
	FrecuencyTable(const Dataset<T>& data)
	{
		categorie next = data.min();
		//for(categorie cat = 1 ; cat <= data.categories(); cat++)
		while(next < data.max())
		{
			Frecuency<T> row;
			row.min = next;
			row.max = next + data.amplitude();
			row.frec = 0;
			for(T d : data)
			{
				if(d >= row.min and d < row.max) row.frec++;
			}
			std::list<Frecuency<T>>::push_back(row);
			next += data.amplitude();
		}
	};
};
}

#endif