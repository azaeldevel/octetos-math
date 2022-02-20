#ifndef OCTETOS_MATH_STATICS_OPS_HH
#define OCTETOS_MATH_STATICS_OPS_HH

#include <vector>
#include <list>

namespace oct::sta
{

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mean
	template <typename D,typename T = D> T mean(const std::vector<D>& c)
	{
		T m = 0;

		for(typename std::vector<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename T = D> T mean(const std::vector<D>& c,const T& (*getter)(const D&))
	{
		T m = 0;

		for(typename std::vector<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename T = D> T mean(const std::list<D>& c)
	{
		T m = 0;

		for(typename std::list<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
		}

		m /= T(c.size());
		return m;
	}
	template <typename D,typename T = D> T mean(const std::list<D>& c,const T& (*getter)(const D&))
	{
		T m = 0;

		for(typename std::list<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += getter(*it);
		}

		m /= T(c.size());
		return m;
	}





	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>sigma
	template <typename D,typename T = D> T variation(const std::vector<D>& c)
	{
		T m = mean(c);
		T s = 0;

		for(typename std::vector<D>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			s += std::pow(*it - m,T(2));
		}

		s /= T(c.size());
		return s;
	}
}

#endif