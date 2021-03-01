

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
	class Identity : public Function<T>
	{
	public:
		//
		Identity(Domain<T>& d, short dim) : Function<T>(d,dim)
		{
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return a;
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		};

		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	};

	template<class T>
	class Constant : public Function<T>
	{
	public:
		//
		Constant(T c, short dim) : Function<T>(NULL,dim)
		{
			this->c = c;
		};
		Constant(Domain<T>& d,T c, short dim) : Function<T>(d,dim)
		{
			this->c = c;
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return c;
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
		T c;
	};
	
	template<class T>
	class Square : public Function<T>
	{
	public:
		//
		Square(Domain<T>& d, short dim) : Function<T>(d,dim)
		{
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return sqrt(a);
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
	};

	template<class T>
	class Power : public Function<T>
	{
	public:
		//
		Power(Domain<T>& d, T power) : Function<T>(d)
		{
			this->power = power;
		};
		virtual T operator() (T a)
		{
			return pow(a,power);
		};

		virtual T lim(T n)
		{
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
		T power;
	};

	template<class T>
	class Polinomio : public Function<T>
	{
	public:
		//
		Polinomio(Domain<T>& d, const std::vector<T>& coefs) : Function<T>(d)
		{//[1] pag 139
			grade = coefs.size() + 1;
		};
		virtual T operator() (T a)
		{
			T temp = 0;

			for(short i = 0 ; i < coefs.size(); i++)
			{
				temp += coefs[i] * (pow(a,i));
			}

			return temp;
		};

		virtual T lim(T n)
		{
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
		const std::vector<T>& coefs;
		short grade;
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
		List(const std::map<T,T>& c, short dim): Function<T>(new Valid<T>(c),dim),coordenadas(c)
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
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
		const std::map<T,T>& coordenadas;
		
	};

	template<class T>
	class Parabolic : public Function<T>
	{
	public:
		//
		Parabolic(Domain<T>& d, short dim,T b) : Function<T>(d,dim),base(b)
		{
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return pow(a,2) + base;
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		};

		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
		T base;
	};

	//Operations>>>>>>>>>>>>
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
		Operator(Function<T>& f, short dim) : Function<T>(NULL,f.getDimension())
		{
			fs.push_back(&f);
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	protected:
		std::vector<Function<T>*> fs;
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
		SecantLine(Function<T>& f,T into,std::list<math::Point<T>>& l,T divisor) : Operator<T>(f,f.getDimension()),in(into),list(l),div(divisor)
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
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
		T in;
		std::list<math::Point<T>>& list;
		T div;
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
			for(Function<T>* f : this->fs)
			{
				if(!f->check(a))
				{
					std::string msg = "El valor '";
					msg += std::to_string(a) + "', esta fuera del Dominio.";
					throw octetos::core::Exception(msg,__FILE__,__LINE__);
				}
			}
			T temp = 0;
			for(Function<T>* f : this->fs)
			{
				temp += (*f)(a);
			}
			return temp;
		};
		virtual T lim(T a)
		{
			return this->operator()(a);
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
	};
	
	template<class T>
	class Multiplication : public Operator<T>
	{
	public:
		//
		Multiplication(Function<T>& f, Function<T>& g): Operator<T>(f,g)	
		{
		};
		virtual T operator() (T a)
		{
			for(Function<T>* f : this->fs)
			{
				if(!f->domain->check(a))
				{
					std::string msg = "El valor '";
					msg += std::to_string(a) + "', esta fuera del Dominio.";
					throw octetos::core::Exception(msg,__FILE__,__LINE__);
				}
			}
			T temp = 0;
			for(Function<T>* f : this->fs)
			{
				temp *= (*f)(a);
			}
			return temp;
		};
		virtual T lim(T n)
		{
		};
		virtual T D()
		{
		};
		virtual T S()
		{
		};
	private:
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
		virtual T D()
		{
			
		};
		virtual T S()
		{
			
		};
	private:
	};

}


#endif