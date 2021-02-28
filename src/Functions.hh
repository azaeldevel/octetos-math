

#ifndef OCTETOS_MATH_FUNCTIONS_HH
#define OCTETOS_MATH_FUNCTIONS_HH

#include <map>

namespace math
{
	template<class T>
	class Domain
	{
	public:
		virtual bool check(T a) const = 0;
	};

	template<class T>
	class Interval : public Domain<T>
	{
	};

	template<class T>
	class Unbounded : public Interval<T>
	{
	public:
		Unbounded(T a)
		{
			this->a = a;
		};
		
	public:
		T a;
	};


	template<class T>
	class Bounded : public Unbounded<T>
	{
	public:
		Bounded(T a, T b) : Unbounded<T>(a)
		{
			this->b = b;
		};
		
	public:
		T b;
	};

	template<class T>
	class IntevalClosed : public Bounded<T>
	{
	public:
		IntevalClosed(T a, T b) : Bounded<T>(a,b)
		{
		};
		
		virtual bool check(T i) const
		{
			return i >= this->a and i <= this->b;
		}; 
	};

	template<class T>
	class IntervalOpen : public Bounded<T>
	{
	public:
		IntervalOpen(T a, T b) : Bounded<T>(a,b)
		{
		};
		virtual bool check(T i) const
		{
			return i > this->a and i < this->b;
		}; 
	};

	template<class T>
	class Naturals : public Domain<T>
	{
		virtual bool check(T i) const
		{
			long tmp = (long)i;
			T n = tmp;
			if( (i - n) <= math::epsilon) return true;
			return false;
		};
	};

	template<class T>
	class NotNegative : public Domain<T>
	{
		virtual bool check(T i) const
		{
			if( i < 0.0) return false;
			return true;
		};
	};

	
	template<class T>
	class Set : public Domain<T>, public std::vector<T>
	{
	public:
		Set(double from, double to, double delta) : std::vector<T>()
		{
			for(double i = 0.0; i - to < math::epsilon; i = i + delta)
			{
				add(i);
			};
		};
		Set(long from, long to, long delta)
		{
			for(long i = 0; i < to; i = i + delta)
			{
				add(i);
			};
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
	class Function
	{
	public:
		//
		Function(Domain<T>& d) : domain(&d)
		{	
		};
		//evaluation
		virtual T operator() (T a) = 0;

		//
		bool check(T a)  const
		{
			if(domain)return domain->check(a);
			return false;
		};

		double inverAdd(double a) const
		{
			return -1.0 * (*this)(a);
		};
		double inverMult(double a) const
		{
			return 1.0 / (*this)(a);
		};
		float inverAdd(float a) const
		{
			return -1.0 * (*this)(a);
		};
		float inverMult(float a) const
		{
			return 1.0 / (*this)(a);
		};
		
		long inverAdd(long a) const
		{
			return -1 * (*this)(a);
		};
		long inverMult(long a) const
		{
			return 1 / (*this)(a);
		};
		int inverAdd(int a) const
		{
			return -1 * (*this)(a);
		};
		int inverMult(int a) const
		{
			return 1 / (*this)(a);
		};

		//funciones
		bool isUnivalente(T x1, T x2) const
		{//[1] pag 146
			if( x1 - x2 < math::epsilon)
			{
				
			}
			else
			{
				throw math::Exception("Para determinar la univalecia de una fucnio se requieren que los valores de prueba sean iguales",__FILE__,__LINE__);
			}

			return false;
		};
		virtual T lim(T n) = 0;
		virtual T D() = 0;
		virtual T S() = 0;
	protected:
		Domain<T>* domain;

		//
		Function(Domain<T>* d) : domain(d)
		{
		};
	};

	template<class T>
	class Identity : public Function<T>
	{
	public:
		//
		Identity(Domain<T>& d) : Function<T>(d)
		{
		};
		virtual T operator() (T a)
		{
			return a;
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
	};

	template<class T>
	class Constant : public Function<T>
	{
	public:
		//
		Constant(T c) : Function<T>(NULL)
		{
			this->c = c;
		};
		Constant(Domain<T>& d,T c) : Function<T>(d)
		{
			this->c = c;
		};
		virtual T operator() (T a)
		{
			return c;
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
		T c;
	};

	template<class T>
	class Square : public Function<T>
	{
	public:
		//
		Square(Domain<T>& d) : Function<T>(d)
		{
		};
		virtual T operator() (T a)
		{
			if(this->domain->check(a)) return sqrt(a);
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
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
	class Operation : public Function<T>
	{
	public:
		//
		Operation(Function<T>& f, Function<T>& g) : Function<T>(NULL)
		{
			fs.push_back(&f);
			fs.push_back(&g);
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
	protected:
		std::vector<Function<T>*> fs;
	};

	template<class T>
	class Sum : public Operation<T>
	{
	public:
		//
		Sum(Function<T>& f, Function<T>& g) : Operation<T>(f,g)
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
	class Multiplication : public Operation<T>
	{
	public:
		//
		Multiplication(Function<T>& f, Function<T>& g): Function<T>(f,g)	
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
				temp += (*f)(a);
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
	class Coordenadas : public Function<T>
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
		Coordenadas(const std::map<T,T>& c): Function<T>(new Valid<T>(c)),coordenadas(c)	
		{
		};
		virtual T operator() (T a)
		{
			return coordenadas.at(a);
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
		const std::map<T,T>& coordenadas;
		
	};

	template<class T>
	class Composition : public Operation<T>
	{//[1] pag 141
	public:
		//
		Composition(Function<T>& f, Function<T>& g) : Operation<T>(f,g)
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

}


#endif