#ifndef OCTETOS_MATH_STATICS_HH
#define OCTETOS_MATH_STATICS_HH

#include <list>
#include<algorithm>
#if defined(__linux__)
    #include <octetos/core/Exception.hh>
#elif (defined(_WIN32) || defined(_WIN64))
    #include <Exception.hh>
#else
    #error "Pltaforma desconocida"
#endif

#include "core.hh"

namespace oct::math
{

typedef unsigned int categorie;

template<typename T> class IData
{
public:
	virtual operator T() = 0;
};

template<typename T>
class Dataset : public std::list<T>
{
public:

public:
	Dataset()
	{
		sorted = false;
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
	unsigned int amplitudeClass()const
	{
		return range()/categories();
	}

	void sort()
	{
		std::list<T>::sort(cmpDesc);
		sorted = true;
	};


	double mean() const
	{
		double m = 0;
		for(T t : *this)
		{
			m += double(t);
		}
		m /= double(counter());

		return m;
	}
	T median() const
	{
		if(not sorted) throw octetos::core::Exception("El conjunto de datos no esta ordenado");

		bool par = (counter() % 2) == 0;

		if(par)
		{
			unsigned int m = counter()/2;
			auto it1 = std::list<T>::begin();
			std::advance(it1,m);
			auto it2 = std::list<T>::begin();
			std::advance(it2,m + 1);

			return (*it1 + *it2)/2.0;
		}
		else
		{
			auto it = std::list<T>::begin();
			std::advance(it,(counter()+1)/2);
			return *it;
		}
	}

	T mode() const
	{
		struct Frec
		{
			T data;
			unsigned int frec;
		};
		std::list<Frec> frecList;
		T m = 0;
		for(T t : *this)
		{

		}
	}

	double md() const
	{
		double d = 0, m = mean();

		for(T t : *this)
		{
			d += std::abs(double(t) - m);
		}
		d /= double(counter());

		return d;
	}

	double variance(bool population) const
	{
		double d = 0, m = mean();

		for(T t : *this)
		{
			d += pow(double(t) - m,2.0);
		}
		return population ? d / double(counter()) : d / double(counter() - 1.0);
	}

	double sd() const
	{
		return sqrt(md());
	}

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
	double frecr;
	double frecp;
	unsigned int frecaless;
	unsigned int frecageater;
	float frecpaless;
	float frecpagreater;

	T markClass()const
	{
		return (max - min) / 2;
	}
};

template<typename T>
class FrecuencyTable : public std::list<Frecuency<T>>
{
public:
	FrecuencyTable(const Dataset<T>& dt) : data(dt)
	{
		categorie next = data.min();
		//for(categorie cat = 1 ; cat <= data.categories(); cat++)
		while(next < data.max())
		{
			Frecuency<T> row;
			row.min = next;
			row.max = next + data.amplitudeClass();
			row.frec = 0;
			row.frecr = 0;
			row.frecp = 0;
			row.frecaless = 0;
			row.frecageater = 0;
			for(T d : data)
			{
				if(d >= row.min and d < row.max) row.frec++;
			}
			row.frecr = row.frec / data.counter();
			std::list<Frecuency<T>>::push_back(row);
			next += data.amplitudeClass();
		}
	};

	void frecr()
	{
		for(Frecuency<T>& row : *this)
		{
			row.frecr = double(row.frec) / double(data.counter());
		}
	}
	void frecp()
	{
		for(Frecuency<T>& row : *this)
		{
			row.frecp = (100.0 * double(row.frec)) / double(data.counter());
		}
	}
	void frecaless()
	{
		unsigned int f = 0;
		for(Frecuency<T>& row : *this)
		{
			f += row.frec;
			row.frecaless = f;
		}
	}

	void frecageater()
	{
		unsigned int f = 0;
		std::for_each(std::list<Frecuency<T>>::rbegin(),std::list<Frecuency<T>>::rend(),
           	[&f](Frecuency<T>& row)
			{
				f += row.frec;
				row.frecageater = f;
			}
		);
	}

	void frecpaless()
	{
		double f = 0;
		for(Frecuency<T>& row : *this)
		{
			f += row.frecp;
			row.frecpaless = f;
		}
	}
	void frecpageater()
	{
		double f = 0;
		std::for_each(std::list<Frecuency<T>>::rbegin(),std::list<Frecuency<T>>::rend(),
           	[&f](Frecuency<T>& row)
			{
				f += row.frecp;
				row.frecpagreater = f;
			}
		);
	}



private:
	const Dataset<T>& data;
};







	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mean
	template <typename D,typename C,typename T = D> T mean(const C& c)
	{
		T m = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename C,typename T = D> T mean(const C& c,T (*getter)(const D&))
	{
		T m = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename C,typename T = D> T mean(const C& c,T (*getter)(D))
	{
		T m = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	




	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>variation
	template <typename D,typename C,typename T = D> T variation(const C& c,T mean)
	{
		T s = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename C,typename T = D> T variation(C& c,T mean,T (*getter)(const D&))
	{
		T s = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename C,typename T = D> T variation(C& c,T mean,T (*getter)(D))
	{
		T s = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename C,typename T = D> T variation_sample(const C& c,T mean)
	{
		T s = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - mean,T(2));
		}

		s /= T(c.size() - 1);
		return s;
	}
	template <typename D,typename C,typename T = D> T variation_sample(C& c,T mean,T (*getter)(const D&))
	{
		T s = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size() - 1);
		return s;
	}
	template <typename D,typename C,typename T = D> T variation_sample(C& c,T mean,T (*getter)(D))
	{
		T s = 0;

		for(typename C::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size() - 1);
		return s;
	}





	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>sort
	template <typename D,typename T = D> void sort(std::vector<D>& c,bool (*comp)(D,D))
	{
		std::sort(c.begin(),c.end(),comp);
	}
	template <typename D,typename T = D> void sort(std::vector<D>& c,bool (*comp)(D&,D&))
	{
		std::sort(c.begin(),c.end(),comp);
	}

	template <typename D,typename T = D> void sort(std::list<D>& c,bool (*comp)(D,D))
	{
		c.sort(comp);
	}
	template <typename D,typename T = D> void sort(std::list<D>& c,bool (*comp)(D&,D&))
	{
		c.sort(comp);
	}






	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>median
	template <typename D,typename C,typename T = D> T median(const C& c)
	{
		if(c.size() == 1) return c[0];

		unsigned int div = c.size() % 2;

		if(div == 0)
		{
			unsigned int indexB = c.size() / 2;
			unsigned int indexE = indexB + 1;
			T m = c[indexB] + c[indexE];
			m /= T(2);
			return m;
		}
		else
		{
			unsigned int index = (c.size() / 2) + 1;
			return c[index];
		}
	}
	template <typename D,typename C,typename T = D> T median(C& c,T (*getter)(const D&))
	{
		if(c.size() == 1) return getter(c[0]);

		unsigned int div = c.size() % 2;

		if(div == 0)
		{
			unsigned int indexB = c.size() / 2;
			unsigned int indexE = indexB + 1;
			T m = getter(c[indexB]) + getter(c[indexE]);
			m /= T(2);
			return m;
		}
		else
		{
			unsigned int index = (c.size() / 2) + 1;
			return getter(c[index]);
		}
	}


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mode
	template <typename D,typename C,typename T = D> T mode(const C& c)
	{
		std::map<D,unsigned int> list_ordered;
		typename std::map<D,unsigned int>::iterator it;
		T m = 0;
		for(D d : c)
		{
			it = list_ordered.find(d);
			if(it == list_ordered.end()) 
			{
				list_ordered.insert({d,1});
			}
			else
			{
				(*it).second++;
			}
		}
		
		/*for(const std::pair<D,unsigned int>& p : list_ordered)
		{
			std::cout << "(" << p.first << "," << p.second << ")\n";
		}*/
		//std::cout << "\n";
		std::multimap<unsigned int,D,std::greater<D>> list_ordered2;
		for(const std::pair<D,unsigned int>& p : list_ordered)
		{
			list_ordered2.insert({p.second,p.first});
		}
		/*for(const std::pair<unsigned int,D>& p : list_ordered2)
		{
			std::cout << "(" << p.first << "," << p.second << ")\n";
		}*/
		return (*list_ordered2.begin()).second;
	}
}

#endif
