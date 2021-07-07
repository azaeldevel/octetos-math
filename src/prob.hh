

#ifndef OCTETOS_MATH_PROBABILITY_HH
#define OCTETOS_MATH_PROBABILITY_HH

#include "core.hh"

namespace oct::math
{
	enum TypeVariable
	{
		CONTINUE,
		DISCRETE
	};
	
	template<class T>
	class Probability : public Function<T>
	{
	public:
		Probability(TypeVariable t) : type(t)
		{
			
		}

	private:
		TypeVariable type;
	};
}

#endif