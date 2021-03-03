

#ifndef OCTETOS_MATH_FUNCTIONS_EXTENCION_HH
#define OCTETOS_MATH_FUNCTIONS_EXTENCION_HH

#include "funcs.hh"


namespace math::funcs
{
	template<class T>
	class ExerciesSecante : public Function<T>
	{
	public:
		ExerciesSecante(T into,std::list<math::Point<T>>& l,T divisor) : Function<T>(2),in(into),list(l),div(divisor)
		{
		};
		virtual T operator() (T a)
		{
			;
		}
		virtual T lim(T a)
		{
		};
		virtual T D(T a)
		{
		};
		T secsen(T a)
		{			
			T temp = 0;
			T h = in - a;
			T x = 0;
			for(short i = 0; i < 10; i++)
			{
				x = in - h;
				//std::cout << "h = " << h << "\n";
				temp = (sin(in) - sin(x)) / h;
				//std::cout << "f(x) = " << temp << "\n";
				h = h/div;
				list.push_back(math::Point<T>(x,temp));
			}
			return temp;
		}

	private:
		T in;
		std::list<math::Point<T>>& list;
		T div;
	};
}

#endif 
