

#ifndef OCTETOS_MATH_FUNCTIONS_HH
#define OCTETOS_MATH_FUNCTIONS_HH

#include "core.hh"
#include "Intervals.hh"


namespace math::funcs
{
	template<class T> class Multiply;
	template<class T> class Power;
	template<class T> class Cos;

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
	class C : public Function<T>
	{
	public:
		//
		C(Domain<T>& d,T c) : Function<T>(d)
		{
			this->c = c;
		};
		C(T c) : Function<T>(NULL)
		{
			this->c = c;
		};
		virtual ~C()
		{			
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return c;
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
		virtual C<T>& D()
		{
			Equation<T>* e = new C<T>(0);
			this->addDeletes(e);
			return (C<T>&)*e;
		};
	private:
		T c;
	};

	template<class T>
	class I : public Function<T>
	{
	public:
		//
		I(Domain<T>& d) : Function<T>(d)
		{
		};
		I(Domain<T>* d) : Function<T>(d)
		{
		};
		virtual ~I()
		{			
		};
		virtual T operator() (T a)
		{
			if(Function<T>::check(a)) return a;
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};
		virtual C<T>& D()
		{
			Equation<T>* t = new C<T>(1);
			this->addDeletes(t);
			return (C<T>&)* t;
		};
	};

	


	//>>Operator
	template<class T>
	class Operator : public Function<T>
	{
	public:
		//
		Operator(Equation<T>& f, Equation<T>& g) : Function<T>(NULL)
		{
			fs.push_back(&f);			
			fs.push_back(&g);
		};
		Operator(Equation<T>& f) : Function<T>(NULL)
		{
			fs.push_back(&f);
		};
		virtual ~Operator()
		{			
		};
		virtual bool check(T a) const
		{
			for(Equation<T>* f : fs)
			{
				if(!f->check(a)) return false;
			}
			
			return true;
		}
		void add(Equation<T>& f)const
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
		std::vector<Equation<T>*> fs;
	};
	

	template<class T>
	class Composition : public Operator<T>
	{//[1] pag 141
	public:
		//
		Composition(Equation<T>& f, Equation<T>& g) : Operator<T>(f,g)
		{
		};
		virtual ~Composition()
		{			
		};
		virtual T operator()(T a)
		{
			Equation<T>& g = *(this->fs[1]);
			Equation<T>& f = *(this->fs[0]);
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
		virtual Equation<T>& D()
		{
			
			Equation<T>& g = *(this->fs[1]);
			Equation<T>& f = *(this->fs[0]);
			Composition<T> * comp1 = new Composition(f.D(),g);
			Multiply<T>* mul1 = new Multiply<T>((Equation<T>&)*comp1,g.D());
			this->addDeletes(comp1);
			this->addDeletes(mul1);
			return * mul1;
		};
	private:
	};


	template<class T>
	class Sum : public Operator<T>
	{
	public:
		//
		Sum(Equation<T>& f, Equation<T>& g) : Operator<T>(f,g)
		{
		};
		virtual ~Sum()
		{			
		};
		virtual T operator() (T a)
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];

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
		virtual Equation<T>& D()
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];
			Equation<T>* e = new Sum(f.D(),g.D());
			this->addDeletes(e);		
			return * e;
		};
	private:
	};


	template<class T>
	class cF : public Operator<T>
	{
	public:
		//
		cF(T cval, Equation<T>& f) : Operator<T>(f),c(cval)
		{
		};
		cF(Domain<T>& d,T cval, short dim) : Function<T>(d,dim),c(cval)
		{
		};
		virtual ~cF()
		{			
		};
		virtual T operator() (T a)
		{
			if(Operator<T>::fs.size() > 0)
			{
				Equation<T>& f = *(Operator<T>::fs[0]);
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
		virtual Equation<T>& D()
		{
			Equation<T>& f = *(Operator<T>::fs[0]);
			cF<T>* newcf = new cF<T>(c,f.D());
			this->addDeletes(newcf);
			return * newcf;
		};
	private:
		T c;
	};
	

	

	template<class T>
	class Minus : public Operator<T>
	{
	public:
		//
		Minus(Equation<T>& f, Equation<T>& g) : Operator<T>(f,g)
		{
		};
		virtual ~Minus()
		{			
		};
		virtual T operator() (T a)
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];

			if(!f.check(a) and !g.check(a))
			{
				std::string msg = "El valor '";
				msg += std::to_string(a) + "', esta fuera del Dominio.";
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
			return f(a) - g(a);
		};
		virtual Minus<T>& D()
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];
			Minus<T>* e = new Minus(f.D(),g.D());
			this->addDeletes(e);		
			return * e;
		};
	private:
	};

	template<class T>
	class Multiply : public Operator<T>
	{
	public:
		//
		Multiply(Equation<T>& f, Equation<T>& g): Operator<T>(f,g)	
		{
		};
		virtual ~Multiply()
		{			
		};
		virtual T operator() (T a)
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];

			if(!f.check(a) and !g.check(a))
			{
					std::string msg = "El valor '";
					msg += std::to_string(a) + "', esta fuera del Dominio.";
					throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
			return f(a) * g(a);
		};
		virtual Equation<T>& D()
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];
			Multiply<T>* comp1 = new Multiply<T>(f,g.D());
			Multiply<T>* comp2 = new Multiply<T>(g,f.D());
			Sum<T>* sum1 = new Sum<T>(*comp1,*comp2);
			return (Equation<T>&) * sum1;
		};
	private:
	};
	
	template<class T>
	class Divide : public Operator<T>
	{
	public:
		//
		Divide(Equation<T>& f, Equation<T>& g): Operator<T>(f,g)	
		{
		};
		virtual ~Divide()
		{			
		};
		virtual T operator() (T a)
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];

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
		virtual Equation<T>& D()
		{
			Equation<T>& f = *Operator<T>::fs[0];
			Equation<T>& g = *Operator<T>::fs[1];
			Multiply<T>* comp1 = new Multiply<T>(f.D(),g);
			Multiply<T>* comp2 = new Multiply<T>(g,f.D());
			Minus<T>* min1 = new Minus<T>(*comp1,*comp2);
			Power<T>* pow1 = new Power<T>(g,2.0);
			Divide<T>* dic1 = new Divide<T>(*min1,*pow1);
			this->addDeletes(comp1);
			this->addDeletes(comp2);
			this->addDeletes(min1);
			this->addDeletes(pow1);
			this->addDeletes(dic1);
			return (Equation<T>&) * dic1;
		};
	private:
	};
	
	template<class T>
	class Power : public Operator<T>
	{
	public:
		//
		Power(Equation<T>& d, T p) : Operator<T>(d),power(p)
		{
		};
		virtual ~Power()
		{			
		};
		virtual T operator() (T a)
		{
			Equation<T>& f = *(Operator<T>::fs[0]);
			if(f.check(a))
			{
				return pow(f(a),power);
			}
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw Exception(msg,__FILE__,__LINE__);
		};

		virtual Equation<T>& D()
		{
			Equation<T>* f = Operator<T>::fs[0];			
			Power<T>* newF = new Power<T>(*f,power-1);
			cF<T>* cfnew = new cF<T>(power,*newF);
			this->addDeletes(newF);
			this->addDeletes(cfnew);
			return *cfnew;
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
		virtual ~Parabolic()
		{			
		};
		virtual T operator() (T a)
		{
			if(Power<T>::check(a)) return Power<T>::operator()(a);
			
			std::string msg = "El valor '";
			msg += std::to_string(a) + "', esta fuera del Dominio.";
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		};
		virtual cF<T>& D()
		{
			Equation<T>* e1 = new I<T>(Equation<T>::getDomain());
			Equation<T>* e2 = new cF<T>(2.0,* e1);
			this->addDeletes(e1);
			this->addDeletes(e2);
			return (cF<T>&)*e2;
		};
	private:
		T base;
	};
	

	template<class T>
	class Sin : public Function<T>
	{
	public:
		//
		Sin(Domain<T>& d): Function<T>(d)	
		{
		};
		virtual ~Sin()
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
		virtual Equation<T>& D()
		{
			Equation<T>* e1 = new Cos<T>(this->getDomain());
			this->addDeletes(e1);
			return *e1;
		};
	};
	
	template<class T>
	class Cos : public Function<T>
	{
	public:
		//
		Cos(Domain<T>& d): Function<T>(d)	
		{
		};
		virtual ~Cos()
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
		virtual Equation<T>& D()
		{
			Equation<T>* e1 = new Sin<T>(this->getDomain());
			cF<T>* e2 = new cF<T>(-1.0,*e1);
			this->addDeletes(e1);
			this->addDeletes(e2);
			return *e2;
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
		List(const std::map<T,T>& c) : Function<T>(new Valid<T>(c)),coordenadas(c)
		{
			
		};
		virtual T operator() (T a)
		{
			return coordenadas.at(a);
		};
		virtual Equation<T>& D()
		{
			
		};
		virtual ~List()
		{			
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
		virtual ~SecantLine()
		{			
		};
		virtual T operator() (T a)
		{
			Equation<T>& f = *(this->fs.at(0));
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
		virtual Equation<T>& D()
		{
		};
	private:
		T in;
		std::list<math::Point<T>>& list;
		T div;
	};
}


#endif