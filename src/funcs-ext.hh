

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
			return 0;
		}
		virtual T lim(T a)
		{
			return 0;
		};
		virtual T D(T a)
		{
			return 0;
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

	template<class T>
	class VolumenTubo : public Function<T>
	{//[1] pag 398
	public:
		/*
		*
		*\param higth altura del tubo en metro
		*\param diametro diametros exterior del tubo en metros
		*/
		VolumenTubo(Domain<T>& d, T higth, T diametro) : Function<T>(d,2), h(higth), d(diametro)
		{
			
		};
		
		virtual T operator() (T a)
		{
			if(!Function<T>::check(a))
			{
				std::string msg = "El valor '";
				msg += std::to_string(a) + "', esta fuera del Dominio.";
				
				throw Exception(msg,__FILE__,__LINE__);
			}
			
			return h * M_PI * pow(a,2);
		}
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		//a es el radio interior
		virtual T D(T a)
		{
			T r = d/2;
			//std::cout << "h = " << h << "\n";
			//std::cout << "r = " << r << "\n";
			return 2 * h * M_PI * r;
		};

	private:
		T h,d;
	};
}

#endif 
