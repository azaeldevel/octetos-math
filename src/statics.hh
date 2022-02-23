#ifndef OCTETOS_MATH_STATICS_HH
#define OCTETOS_MATH_STATICS_HH


#include<algorithm>
#if defined(__linux__)
    
#elif (defined(_WIN32) || defined(_WIN64))
    
#else
    #error "Pltaforma desconocida"
#endif

#include "core.hh"

namespace oct::math
{
	
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mean
	template <typename D,template<typename> typename C,typename T = D> T mean(const C<D>& c)
	{
		T m = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,template<typename> typename C,typename T = D> T mean(const C<D>& c,T (*getter)(const D&))
	{
		T m = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,template<typename> typename C,typename T = D> T mean(const C<D>& c,T (*getter)(D))
	{
		T m = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	




	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>variation
	template <typename D,template<typename> typename C,typename T = D> T variation(const C<D>& c,T mean)
	{
		T s = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,template<typename> typename C,typename T = D> T variation(const C<D>& c,T mean,T (*getter)(const D&))
	{
		T s = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,template<typename> typename C,typename T = D> T variation(const C<D>& c,T mean,T (*getter)(D))
	{
		T s = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size());
		return s;
	}
	template <typename D,template<typename> typename C,typename T = D> T variation_sample(const C<D>& c,T mean)
	{
		T s = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - mean,T(2));
		}

		s /= T(c.size() - 1);
		return s;
	}
	template <typename D,template<typename> typename C,typename T = D> T variation_sample(const C<D>& c,T mean,T (*getter)(const D&))
	{
		T s = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(getter(*it) - mean,T(2));
		}

		s /= T(c.size() - 1);
		return s;
	}
	template <typename D,template<typename> typename C,typename T = D> T variation_sample(C<D>& c,T mean,T (*getter)(const D&))
	{
		T s = 0;

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
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
	template <typename D,template<typename> typename C,typename T = D> T median(const C<D>& c)
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
	template <typename D,template<typename> typename C,typename T = D> T median(const C<D>& c,T (*getter)(const D&))
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
	template <typename D,template<typename> typename C,typename T = D> void mode(const C<D>& c,T& value,unsigned int& modal)
	{
		std::map<D,unsigned int> list_ordered;
		typename std::map<D,unsigned int>::iterator it;
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
		unsigned int m1 = (*list_ordered2.begin()).first;
		modal = 0;
		if(m1 == 1)
		{
			value = (*list_ordered2.begin()).second;
		}
		for(const std::pair<unsigned int,D>& p : list_ordered2)
		{
			if(m1 == p.first) modal++;
		}
		/*for(const std::pair<unsigned int,D>& p : list_ordered2)
		{
			std::cout << "(" << p.first << "," << p.second << ")\n";
		}*/
		value = (*list_ordered2.begin()).second;
	}


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>max
	template <typename D,template<typename> typename C,typename T = D> T max(const C<D>& c)
	{
		T m = c.front();

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			if(*it > m) m = *it;
		}

		return m;
	}






	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>min
	template <typename D,template<typename> typename C,typename T = D> T min(const C<D>& c)
	{
		T m = c.front();

		for(typename C<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			if(*it < m) m = *it;
		}

		return m;
	}




	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>frecuency_table
	template <typename D,template<typename> typename C,typename T = D> struct class_data
	{
		T data;
		unsigned int frecuency;
	};
	template <typename D,template<typename> typename C,typename T = D> class frecuency_table : protected std::list<class_data<D,C,T>>
	{
	public:
		/**
		*
		*/
		frecuency_table(T intereval,unsigned int class_counter) : by_interval(true)
		{
		}
		
		/**
		*
		*/
		frecuency_table(unsigned int class_counter) : by_interval(false)
		{
			
		}

		void read(const C<D>& c)
		{
			T mn = min(c);
			T mx = max(c);

			
		}

	private:
		bool by_interval;
		
	};
}

#endif
