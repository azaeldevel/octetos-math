

#ifndef OCTETOS_MATH_FUNCTIONS_HH
#define OCTETOS_MATH_FUNCTIONS_HH

#include "core.hh"
#include "Intervals.hh"


namespace math::funcs
{

	template<class T>
	class Parameters : public Domain<T>, public Set<T>
	{
	public:
		Parameters(double from, double to, double delta) : Set<T>(from,to,delta)
		{
		};
		Parameters(long from, long to, long delta) : Set<T>(from,to,delta)
		{
		};
		
		virtual bool check(double i) const
		{
			for(T t : *this)
			{
				if(t - i < math::epsilon) return true;
			}

			return false;
		};
		virtual bool check(float i) const
		{
			for(T t : *this)
			{
				if(t - i < math::epsilon) return true;
			}

			return false;
		};
		virtual bool check(long i) const
		{
			for(T t : *this)
			{
				if(t == i) return true;
			}

			return false;
		};
		virtual bool check(int i) const
		{
			for(T t : *this)
			{
				if(t == i) return true;
			}

			return false;
		};
		
		void add(T t)
		{
			return this->push_back(t);
		};
	};

	

	template<class T>
	class I : public Function<T>
	{
	public:
		//
		I(Domain<T>& d, short dim) : Function<T>(d,dim)
		{
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return a;
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};

		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			if(Function<T>::check(a))
			{
				return 1;
			}
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
	};

	template<class T>
	class C : public Function<T>
	{
	public:
		//
		C(T c, short dim) : Function<T>(NULL,dim)
		{
			this->c = c;
		};
		C(Domain<T>& d,short dim,T c) : Function<T>(d,dim)
		{
			this->c = c;
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return c;
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			if(Function<T>::check(a))
			{
				return 0;
			}
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
	private:
		T c;
	};


	//>>Operator
	template<class T>
	class Operator : public Function<T>
	{
	public:
		//
		Operator(Function<T>& f, Function<T>& g) : Function<T>(NULL,f.getDimension())
		{
			if(f.getDimension() != g.getDimension())
			{
				throw Exception("Ambas funciones deme ser de la misma dimension'",__FILE__,__LINE__);
			}
			fs.push_back(&f);			
			fs.push_back(&g);
		};
		Operator(Function<T>& f) : Function<T>(NULL,f.getDimension())
		{
			fs.push_back(&f);
		};
		bool check(T a) const
		{
			for(Function<T>* f : fs)
			{
				if(!f->check(a)) return false;
			}
			
			return true;
		}
		void add(Function<T>& f)const
		{
			if(fs.size() > 0)
			{
				Function<T>& firstF = *fs[0];
				if(firstF.getDimension() != firstF.getDimension())
				{
					throw Exception("Ambas funciones deme ser de la misma dimension'",__FILE__,__LINE__);
				}
			}
			fs.push_back(&f);
		};
	protected:
		std::vector<Function<T>*> fs;
	};
	

	template<class T>
	class Composition : public Operator<T>
	{//[1] pag 141
	public:
		//
		Composition(Function<T>& f, Function<T>& g) : Operator<T>(f,g)
		{
		};
		virtual T operator()(T a)
		{
			Function<T>& g = *(this->fs[1]);
			Function<T>& f = *(this->fs[0]);
			if(g.check(a))
			{
				if(f.check(g(a)))
				{
					return f(g(a));
				}
				else
				{
					std::string msg = "El valor '";
					msg += std::to_string(a) + "', esta fuera del Dominio f.";
					throw octetos::core::Exception(msg,__FILE__,__LINE__);
				}
			}
			else
			{
				std::string msg = "El valor '";
				msg += std::to_string(a) + "', esta fuera del Dominio de g.";
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& g = *(this->fs[1]);
			Function<T>& f = *(this->fs[0]);
			return f.D(g(a))*g.D(a);
		};
	private:
	};

	template<class T>
	class cF : public Operator<T>
	{
	public:
		//
		cF(T cval, Function<T>& f) : Operator<T>(f),c(cval)
		{
		};
		cF(Domain<T>& d,T cval, short dim) : Function<T>(d,dim),c(cval)
		{
		};
		virtual T operator() (T a)
		{
			if(Operator<T>::fs.size() > 0)
			{
				Function<T>& f = *(Operator<T>::fs[0]);
				if(f.check(a)) 
				{
					return c*f(a);
				}
			}
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& f = *(Operator<T>::fs[0]);
			if(f.check(a))
			{
				return c * f.D(a);
			}

			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
	private:
		T c;
	};
	

	template<class T>
	class Sum : public Operator<T>
	{
	public:
		//
		Sum(Function<T>& f, Function<T>& g) : Operator<T>(f,g)
		{
		};
		virtual T operator() (T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];

			if(!f.check(a) and !g.check(a))
			{
					std::string msg = "El valor '";
					msg += std::to_string(a) + "', esta fuera del Dominio.";
					throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
			return f(a) + g(a);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];
			return f.D(a) + g.D(a);
		};
	private:
	};

	template<class T>
	class Minus : public Operator<T>
	{
	public:
		//
		Minus(Function<T>& f, Function<T>& g) : Operator<T>(f,g)
		{
		};
		virtual T operator() (T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];

			if(!f.check(a) and !g.check(a))
			{
				std::string msg = "El valor '";
				msg += std::to_string(a) + "', esta fuera del Dominio.";
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
			return f(a) - g(a);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];
			return f.D(a) - g.D(a);
		};
	private:
	};

	template<class T>
	class Multiply : public Operator<T>
	{
	public:
		//
		Multiply(Function<T>& f, Function<T>& g): Operator<T>(f,g)	
		{
		};
		virtual T operator() (T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];

			if(!f.check(a) and !g.check(a))
			{
					std::string msg = "El valor '";
					msg += std::to_string(a) + "', esta fuera del Dominio.";
					throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
			return f(a) * g(a);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];
			return (f(a)*g.D(a)) + (g(a) * f.D(a));
		};
	private:
	};
	
	template<class T>
	class Divide : public Operator<T>
	{
	public:
		//
		Divide(Function<T>& f, Function<T>& g): Operator<T>(f,g)	
		{
		};
		virtual T operator() (T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];

			if(!f.check(a) and !g.check(a))
			{
				std::string msg = "El valor '";
				msg += std::to_string(a) + "', esta fuera del Dominio.";
				
				throw Exception(msg,__FILE__,__LINE__);
			}
			return f(a) / g(a);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			Function<T>& g = *Operator<T>::fs[1];
			return ((f(a)*g.D(a)) - (g(a) * f.D(a)))/pow(g(a),2);
		};
	private:
	};
	
	template<class T>
	class Power : public Operator<T>
	{
	public:
		//
		Power(Function<T>& d, T p) : Operator<T>(d),power(p)
		{
		};
		virtual T operator() (T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			if(f.check(a))
			{
				return pow(f(a),power);
			}
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};

		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& f = *Operator<T>::fs[0];
			if(f.check(a))
			{
				if(power == 2)
				{
					return power * f(a);
				}
				else if(power > 2)
				{	
					Power<T> newF(f,power-1);
					return power * newF(a);
				}
			}
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
	private:
		T power;
	};

	template<class T>
	class Parabolic : public Power<T>
	{
	public:
		//
		Parabolic(Function<T>& d) : Power<T>(d,2)
		{
		};
		virtual T operator() (T a)
		{
			if(Power<T>::check(a)) return Power<T>::operator()(a);
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		};

		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			if(Function<T>::check(a)) return 2 * a;
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
	private:
		T base;
	};
	

	template<class T>
	class Sin : public Function<T>
	{
	public:
		//
		Sin(Domain<T>& d): Function<T>(d,2)	
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
			
			return ::sin(a);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			return ::cos(a);
		};
	};
	
	template<class T>
	class Cos : public Function<T>
	{
	public:
		//
		Cos(Domain<T>& d): Function<T>(d,2)	
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
			
			return ::cos(a);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			return -1 * ::sin(a);
		};
	};

	template<class T>
	class List : public Function<T>
	{
	private:
		//
		template<class U>
		class Valid : public Domain<U>
		{
		public:
			Valid(const std::map<U,U>& c) : coordenadas(c)
			{
			
			};
			virtual bool check(U i) const
			{
				if(coordenadas.find(i) != coordenadas.end()) return true;
				return false;
			};
		private:
			const std::map<U,U>& coordenadas;
		};
	public:
		//
		List(const std::map<T,T>& c) : Function<T>(new Valid<T>(c),2),coordenadas(c)
		{
		};
		virtual T operator() (T a)
		{
			return coordenadas.at(a);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			return 0;
		};
	private:
		const std::map<T,T>& coordenadas;
		
	};

	template<class T>
	class SecantLine : public Operator<T>
	{
	public:
		/**
		*\brief Optine la secuante para la fucion indicada
		*\param x Valor hacia el que tiene la funcion, en la definion de derivada el valor hacia el que teine la variable
		*\param d Mejor llamada delta, valor de incremento en cada llamada de la fucion
		*\param delta = |x - x0| / div
		**/
		SecantLine(Function<T>& f,T into,std::list<math::Point<T>>& l,T divisor) : Operator<T>(f),in(into),list(l),div(divisor)
		{
		};
		virtual T operator() (T a)
		{
			Function<T>& f = *(this->fs.at(0));
			if(!f.check(a))
			{
				std::string msg = "El valor '";
				msg += std::to_string(a) + "', esta fuera del Dominio.";
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
			T temp = 0;
			T h = in - a;
			T x = 0;
			for(short i = 0; i < 10; i++)
			{
				x = in - h;
				//std::cout << "h = " << h << "\n";
				temp = (f(in) - f(x)) / h;
				//std::cout << "f(x) = " << temp << "\n";
				h = h/div;
				list.push_back(math::Point<T>(x,temp));
			}
			return temp;
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D(T a)
		{
			Function<T>& f = *(this->fs.at(0));
			if(f.check(a)) return 0;

			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		};
	private:
		T in;
		std::list<math::Point<T>>& list;
		T div;
	};
}


#endif