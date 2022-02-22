
#ifndef OCTETOS_MATH_CORE_HH
#define OCTETOS_MATH_CORE_HH

#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <map>
#include <type_traits>
#include <iostream>
#include <memory>
#if defined(__linux__)
    #include <octetos/core/Exception.hh>
#elif (defined(_WIN32) || defined(_WIN64))
    #include <Exception.hh>
#else
    #error "Pltaforma desconocida"
#endif

#include "defines.hh"



#define OCTETOS_MATH_CX 0
#define OCTETOS_MATH_CY 1
#define OCTETOS_MATH_CZ 2


namespace oct::math
{
	typedef OCTETOS_MATH_DECIMAL decimal;
	typedef OCTETOS_MATH_INTEGER integer;

	static decimal epsilon = OCTETOS_MATH_EPSILON;

	class Exception : public octetos::core::Exception
	{
	public:
		Exception(const std::string& msg,const char* fn,int line);
		Exception(const std::string& msg);
	};

	/*template<class T>
	class vector : public std::vector<T>
	{
	public:

	};*/

	template<class T>
	class Measure
	{
	public:
		virtual operator T() const = 0;
	};


	template<class T>
	class Set : public std::vector<T>
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

		void add(T t)
		{
			return this->push_back(t);
		};

		Set<T> U(const Set<T>& obj)
		{
			Set<T> u(*this);//copia el actual

			for(T t : obj)
			{
				if(find(u.begin(),u.end(), t) == u.end())
				{
					u.push_back(t);
				}
			}
			return u;
		};


		Set<T> I(const Set<T>& obj)
		{
			Set<T> u;

			for(T t : *this)
			{
				if(find(obj.begin(),obj.end(), t) != obj.end())
				{
					u.push_back(t);
				}
			}
		};
	};

	/**
	*\brief Dominio de una funcion
	*
	*/
	template<class T>
	class Domain
	{
	public:
		/**
		*\brief Para funciones bidimensionales
		*
		*/
		virtual bool check(T) const = 0;
		virtual bool check(std::vector<T>&) const {return true;};
	};

	template<class T>
	class Equation
	{
	public:
		//
		Equation(Domain<T>& d) : domain(&d)
		{
		};
		Equation(Domain<T>* d) : domain(d)
		{
		};
		virtual ~Equation()
		{
			for(Equation<T>* e : toDelete)
			{
				delete e;
			}
		};


		//getter
		Domain<T>& getDomain()const
		{
			return *domain;
		}

		/**
		*\brief
		*\param p
		**/
		virtual Equation<T>& D() = 0;
		virtual T operator ()(T) = 0;
		virtual void operator ()(std::vector<T>&){};

		virtual bool check(T t) const
		{
			if(domain)return domain->check(t);
			return true;
		}
		virtual bool check(std::vector<T>&) const
		{
			return true;
		};
	protected:
		void addDeletes(Equation<T>* e)
		{
			toDelete.push_back(e);
		};
	private:
		Domain<T>* domain;
		std::list<Equation<T>*> toDelete;

	};

	template<class T>
	class Function : public Equation<T>
	{
	public:
		//
		Function(Domain<T>& d) : Equation<T>(d)
		{
		};
		Function(Domain<T>* d) : Equation<T>(d)
		{
		};
		virtual ~Function()
		{
		};
	};

}



#endif
