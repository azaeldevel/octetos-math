
#ifndef OCTETOS_MATH_CORE_HH
#define OCTETOS_MATH_CORE_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>
#include <cmath>
#include <map>

#include "defines.hh"

namespace math
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
	};

	/**
	*\brief Dominio de una funcion
	*
	*/
	template<class T>
	class Domain
	{
	public:
		virtual bool check(T a) const = 0;
	};
	
	template<class T>
	class Equation
	{
	public:
		//
		Equation(short d) : dimension(d)
		{
		};
		
		//getter
		short getDimension() const
		{
			return dimension;
		}

		//
		virtual T operator() (T a) = 0;
	private:
		short dimension;
	};

	template<class T>
	class Function : public Equation<T>
	{
	public:
		//
		Function(Domain<T>& d,short dim) : domain(&d), Equation<T>(dim)
		{
		};
		Function(Domain<T>* d,short dim) : domain(d), Equation<T>(dim)
		{
		};
		Function(short dim) : domain(NULL),Equation<T>(dim)
		{
		};
		
		//
		bool check(T a) const
		{
			if(domain) return domain->check(a);
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
	private:
		Domain<T>* domain;
		short dimension;
	};
	
} 



#endif