
#ifndef OCTETOS_MATH_INTERVALS_HH
#define OCTETOS_MATH_INTERVALS_HH

#include "core.hh"

namespace math
{
	
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
		
	protected:
		T a;
	};

	template<class T>
	class Positives : public Interval<T>
	{
	public:
		virtual bool check(T a) const
		{
			if(a < 0.0) return false;
			return true;
		};
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
	public:
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

} 

#endif