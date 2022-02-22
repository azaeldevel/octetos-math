#ifndef OCTETOS_MATH_STATICS_HH
#define OCTETOS_MATH_STATICS_HH

#include <list>
#include <octetos/core/Exception.hh>
#include<algorithm>


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
	template <typename D,typename T = D> T mean(std::vector<D>& c)
	{
		T m = 0;

		for(typename std::vector<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename T> T mean(std::vector<D>& c,T (*getter)(D&))
	{
		T m = 0;

		for(typename std::vector<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename T> T mean(std::vector<D>& c,T (*getter)(D))
	{
		T m = 0;

		for(typename std::vector<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	/*template <typename D,typename T> T mean(const std::vector<D*>& c,const T (*getter)(const D*))
	{
		T m = 0;

		for(typename std::vector<D*>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}*/
	template <typename D,typename T = D> T mean(std::list<D>& c)
	{
		T m = 0;

		for(typename std::list<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename T> T mean(std::list<D>& c,T (*getter)(D&))
	{
		T m = 0;

		for(typename std::list<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename T> T mean(std::list<D>& c,T (*getter)(D))
	{
		T m = 0;

		for(typename std::list<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	/*template <typename D,typename T> T mean(const std::list<D*>& c,const T (*getter)(const D*))
	{
		T m = 0;

		for(typename std::list<D*>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}*/





	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>variation
	template <typename D,typename T = D> T variation(std::vector<D>& c,T mean)
	{
		T s = 0;

		for(typename std::vector<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename T = D> T variation(std::vector<D>& c,T mean,T (*getter)(D&))
	{
		T s = 0;

		for(typename std::vector<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename T = D> T variation(std::vector<D>& c,T mean,T (*getter)(D))
	{
		T s = 0;

		for(typename std::vector<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename T = D> T variation_sample(std::vector<D>& c,T mean)
	{
		T s = 0;

		for(typename std::vector<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - mean,T(2));
		}

		s /= T(c.size() - 1);
		return s;
	}	
	template <typename D,typename T = D> T variation(std::list<D>& c,T mean)
	{
		T s = 0;

		for(typename std::list<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename T = D> T variation(std::list<D>& c,T mean,T (*getter)(D&))
	{
		T s = 0;

		for(typename std::list<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,typename T = D> T variation(std::list<D>& c,T mean,T (*getter)(D))
	{
		T s = 0;

		for(typename std::list<D>::iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}





	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>sort
	template <typename D,typename T = D> T sort_asc(D f, D s)
	{
		return f < s;
	}
	template <typename D,typename T = D> T sort_asc(D f, D s,T (*getter)(D))
	{
		return getter(f) < getter(s);
	}
	template <typename D,typename T = D> T sort_desc(D f, D s)
	{
		return f > s;
	}
	template <typename D,typename T = D> T sort_desc(D f, D s,T (*getter)(D))
	{
		return getter(f) > getter(s);
	}
}

#endif