#ifndef OCTETOS_MATH_STATICS_OPS_HH
#define OCTETOS_MATH_STATICS_OPS_HH

#include <vector>
#include <list>

namespace oct::sta
{

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mean
	template <typename T,typename D> T mean(const std::vector<D>& c)
	{
		T m = 0;

		for(typename std::vector<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename T,typename D> T mean(const std::vector<T>& c,const T& (*getter)(const D&))
	{
		T m = 0;

		for(typename std::vector<T>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	template <typename T> T mean(const std::list<T>& c)
	{
		T m = 0;

		for(typename std::list<T>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename T,typename D> T mean(const std::list<D>& c,const T& (*getter)(const D&))
	{
		T m = 0;

		for(typename std::list<T>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}





	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mode
}

#endif