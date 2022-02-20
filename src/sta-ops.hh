#ifndef OCTETOS_MATH_STATICS_OPS_HH
#define OCTETOS_MATH_STATICS_OPS_HH

#include <vector>
#include <list>

namespace oct::sta
{

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mean
	template <typename T> T mean(const std::vector<T>& c)
	{
		T m = 0;

		for(typename std::vector<T>::const_iterator it = c.begin(); it != c.end(); it++)
		{
			m += *it;
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





	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>mode
}

#endif