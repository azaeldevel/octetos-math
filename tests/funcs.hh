
#include <core.hh>

namespace math::funcs
{
	template<class T>
	class VolumenTubo : public Function<T>
	{//[1] pag 398
	public:
		/*
		*
		*\param h altura del tubo
		*/
		VolumenTubo(Domain<T>& d, T higth) : Function<T>(d), h(higth)
		{
		};
		
		virtual T operator() (std::vector<T>& p)
		{
			T temp = h * M_PI * pow(p[0],2);
			p.at(1) = temp;
			return temp;
		}
		//a es el radio interior
		virtual T D(std::vector<T>& p)
		{
			return 2 * h * M_PI * p[0];
		};
		T dV(std::vector<T>& p, T dr)
		{
			return D(p) * dr;
		}
		T peso(std::vector<T>& p, T dr,T m)
		{
			return dV(p,dr) * m;
		}


	private:
		T h;
	};
} 
