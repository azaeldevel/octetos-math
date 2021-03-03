
#ifndef OCTETOS_MATH_CORE_HH
#define OCTETOS_MATH_CORE_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>
#include <cmath>
#include <map>
#include <type_traits>

#include "defines.hh"

#define OCTETOS_MATH_CX 0
#define OCTETOS_MATH_CY 1
#define OCTETOS_MATH_CZ 2

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
	class Point : public std::vector<T>
	{
	public:
		//contructor		
		Point() : std::vector<T>()
		{
		}
		Point(const Point& obj) : std::vector<T>(obj.size())
		{
			Point<T>::at(OCTETOS_MATH_CX) = obj[OCTETOS_MATH_CX];
			Point<T>::at(OCTETOS_MATH_CY) = obj[OCTETOS_MATH_CY];
#if OCTETOS_MATH_DIMENSION >= 3
			Point<T>::at(OCTETOS_MATH_CZ) = obj[OCTETOS_MATH_CZ];
#endif
		}
		Point(T x, T y) : std::vector<T>(2)
		{
			Point<T>::at(OCTETOS_MATH_CX) = x;
			Point<T>::at(OCTETOS_MATH_CY) = y;
	#if OCTETOS_MATH_DIMENSION >= 3
			Point<T>::at(OCTETOS_MATH_CZ) = 0.0;
	#endif
		}
#if OCTETOS_MATH_DIMENSION >= 3
		Point(T x, T y, T z) : std::vector<T>(3)
		{
			Point<T>::at(OCTETOS_MATH_CX) = x;
			Point<T>::at(OCTETOS_MATH_CY) = y;
			Point<T>::at(OCTETOS_MATH_CZ) = z;
		}
#endif
		inline bool checkType()
		{
			if(std::is_same<T, double>::value)
			{
				return true;
			}
			else if(std::is_same<T, long>::value)
			{
				return true;
			}
			else if(std::is_same<T, float>::value)
			{
				return true;
			}
			else if(std::is_same<T, int>::value)
			{
				return true;
			}

			return false;
		}
		//getter
		T getX() const
		{
			if(Point<T>::getDimension() < 1) throw octetos::core::Exception("Obejto vacio",__FILE__,__LINE__);
			return Point<T>::at(OCTETOS_MATH_CX);
		}
		T getY() const
		{
			if(Point<T>::getDimension() < 2) throw octetos::core::Exception("EL obejto no contiene coordenada Y.",__FILE__,__LINE__);
			return Point<T>::at(OCTETOS_MATH_CY);
		}
#if OCTETOS_MATH_DIMENSION >= 3
		T getZ() const
		{
			if(Point<T>::getDimension() < 3) throw octetos::core::Exception("EL obejto no contiene coordenada Z.",__FILE__,__LINE__);
			return Point<T>::at(OCTETOS_MATH_CZ);
		}
#endif
		int getDimension()const
		{
			return Point<T>::size();
		}
		void setX(T val)
		{
			if(Point<T>::getDimension() == 0)
			{
				Point<T>::push_back(val);
			}
			else if(Point<T>::getDimension() >= 1)
			{
				Point<T>::at(OCTETOS_MATH_CX) = val;
			}
			else
			{
				throw octetos::core::Exception("Error desconocido",__FILE__,__LINE__);
			}
		}
		void setY(T val)
		{
			if(Point<T>::getDimension() == 0)
			{
				Point<T>::push_back(0);
				Point<T>::push_back(val);
			}
			else if(Point<T>::getDimension() >= 2)
			{
				Point<T>::at(OCTETOS_MATH_CY) = val;
			}
			else
			{
				throw octetos::core::Exception("El obejto actual no tiene elemento Y",__FILE__,__LINE__);
			}
		}
#if OCTETOS_MATH_DIMENSION >= 3
		void setZ(T val)
		{
			if(Point<T>::getDimension() == 0)
			{
				Point<T>::push_back(0);
				Point<T>::push_back(0);
				Point<T>::push_back(val);
			}
			else if(Point<T>::getDimension() >= 3)
			{
				Point<T>::at(OCTETOS_MATH_CZ) = val;
			}
			else
			{
				throw octetos::core::Exception("El obejto actual no tiene elemento Z",__FILE__,__LINE__);
			}
		}
#endif
		//operators
		operator std::string() const
		{
			std::string str = "(";
			str += std::to_string(Point<T>::at(OCTETOS_MATH_CX)) ;
			str = str + "," + std::to_string(Point<T>::at(OCTETOS_MATH_CY));
#if OCTETOS_MATH_DIMENSION >= 3
			str = str + "," + std::to_string(Point<T>::at(OCTETOS_MATH_CZ));
#endif
			str += ")";
			return str;
		}
		const Point& operator= (const Point& obj)
		{
			if(Point<T>::size() == 0)
			{
				Point<T>::push_back(obj.getX());
				Point<T>::push_back(obj.getY());
#if OCTETOS_MATH_DIMENSION >= 3
				Point<T>::push_back(obj.getZ());
#endif
			}
			else if(Point<T>::size() == obj.size())
			{
				Point<T>::at(OCTETOS_MATH_CX) = obj.getX();
				Point<T>::at(OCTETOS_MATH_CY) = obj.getY();
#if OCTETOS_MATH_DIMENSION >= 3
				Point<T>::at(OCTETOS_MATH_CZ) = obj.getZ();
#endif
			}
			else
			{

			}

			return *this;
		}

		//operator ==
		bool operator ==(const Point<double>& obj)
		{
			if(Point<double>::size() != obj.size()) return false;

			if(fabs(Point<double>::getX() - obj.getX()) > OCTETOS_MATH_EPSILON) return false;
			if(fabs(Point<double>::getY() - obj.getY()) > OCTETOS_MATH_EPSILON) return false;
#if OCTETOS_MATH_DIMENSION >= 3
			if(fabs(Point<double>::getZ() - obj.getZ()) > OCTETOS_MATH_EPSILON) return false;
#endif
			return true;
		}
		bool operator ==(const Point<float>& obj)
		{
			if(Point<float>::size() != obj.size()) return false;

			if(fabs(Point<float>::getX() - obj.getX()) > OCTETOS_MATH_EPSILON) return false;
			if(fabs(Point<float>::getY() - obj.getY()) > OCTETOS_MATH_EPSILON) return false;
#if OCTETOS_MATH_DIMENSION >= 3
			if(fabs(Point<float>::getZ() - obj.getZ()) > OCTETOS_MATH_EPSILON) return false;
#endif
			return true;
		}			
		bool operator ==(const Point<long>& obj)
		{
			if(Point<long>::size() != obj.size()) return false;

			if(Point<long>::getX() != obj.getX()) return false;
			if(Point<long>::getY() != obj.getY()) return false;
#if OCTETOS_MATH_DIMENSION >= 3
			if(Point<long>::getZ() != obj.getZ()) return false;
#endif
			return true;
		}	
		bool operator ==(const Point<int>& obj)
		{
			if(Point<int>::size() != obj.size()) return false;

			if(Point<int>::getX() != obj.getX()) return false;
			if(Point<int>::getY() != obj.getY()) return false;
#if OCTETOS_MATH_DIMENSION >= 3
			if(Point<int>::getZ() != obj.getZ()) return false;
#endif
			return true;
		}


		//funtion
		OCTETOS_MATH_DECIMAL distance(const Point& p)const
		{
			OCTETOS_MATH_DECIMAL lengx = p[OCTETOS_MATH_CX] - Point<T>::at(OCTETOS_MATH_CX);
			OCTETOS_MATH_DECIMAL lengy = p[OCTETOS_MATH_CY] - Point<T>::at(OCTETOS_MATH_CY);
			OCTETOS_MATH_DECIMAL leng = pow(lengx,2) + pow(lengy,2);
#if OCTETOS_MATH_DIMENSION >= 3
			OCTETOS_MATH_DECIMAL lengz = p[OCTETOS_MATH_CZ] - Point<T>::at(OCTETOS_MATH_CZ);
			leng += pow(lengz,2);
#endif
			leng = sqrt(leng);
			return leng;
		}
		
	private:
		
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
		Equation(Domain<T>& d,short dim) : domain(&d), dimension(dim)
		{
		};
		Equation(Domain<T>* d,short dim) : domain(d), dimension(dim)
		{
		};
		Equation(short dim) : domain(NULL),dimension(dim)
		{
		};
		
		//getter
		short getDimension() const
		{
			return dimension;
		}

		//
		bool check(T a) const
		{
			if(domain) return domain->check(a);
			return false;
		};

		//
		virtual T operator() (T a) = 0;
	private:
		short dimension;
		Domain<T>* domain;
	};

	template<class T>
	class Function 
	{
	public:
		//
		Function(Domain<T>& d,short dim) : domain(&d), dimension(dim)
		{
		};
		Function(Domain<T>* d,short dim) : domain(d), dimension(dim)
		{
		};
		Function(short dim) : domain(NULL),dimension(dim)
		{
		};
		
		//getter
		short getDimension() const
		{
			return dimension;
		}
		
		
		//funciones
		virtual T operator() (T a) = 0;
		virtual T lim(T n) = 0;
		virtual T D(T a) = 0;
		virtual void getPoint(Point<T>& p,T a)
		{
			p.setY(this->operator()(a));
			p.setX(a);
		};

		//
		bool check(T a) const
		{
			if(domain) return domain->check(a);
			return true;
		};
		
		//
		T sin(T x){return ::sin(x);};
		T cos(T x){return ::cos(x);};
		T tan(T x){return ::tan(x);};
		//
		
	private:
		short dimension;
		Domain<T>* domain;
	};
	
} 



#endif