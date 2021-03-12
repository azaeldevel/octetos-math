
#ifndef OCTETOS_MATH_CORE_HH
#define OCTETOS_MATH_CORE_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>
#include <cmath>
#include <map>
#include <type_traits>
#include <iostream>


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
	
	enum Unit
	{
		NotUnit,
		
		//distance
		Feet,
		Inch,
		Meter,
		Centimeter,
		Miliemter,
		Feet2,
		Inch2,
		Meter2,
		Centimeter2,
		Miliemter2,
		Feet3,
		Inch3,
		Meter3,
		Centimeter3,
		Miliemter3,

		//velumen
		KilogramByMeter3,
		PoundByFeet3,

		//peso
		Pound,
		Kilogram,
	};
	
	template<class T>
	class Measure 
	{
	public:
		Measure(Unit unit, T value): u(unit),v(value)
		{
		};
		Measure(Unit unit): u(unit)
		{
		};
		
		//operators
		bool operator == (const Measure& obj)const
		{
			if(u != obj.u)
			{
				throw Exception("Los tipos de unidades no coincide.");
			}
			if(v == obj.v) return true;
			return false;
		};
		bool operator == (T v)const
		{
			if(v == v) return true;
			return false;
		};
		bool operator < (const Measure& obj)const
		{
			if(u != obj.u)
			{
				throw Exception("Los tipos de unidades no coincide.");
			}
			if(v < obj.v) return true;
			return false;
		};
		bool operator <= (const Measure& obj)const
		{
			if(u != obj.u)
			{
				throw Exception("Los tipos de unidades no coincide.");
			}
			if(v <= obj.v) return true;
			return false;
		};
		bool operator > (const Measure& obj)const
		{
			if(u != obj.u)
			{
				throw Exception("Los tipos de unidades no coincide.");
			}
			if(v > obj.v) return true;
			return false;
		};
		bool operator >= (const Measure& obj)const
		{
			if(u != obj.u)
			{
				throw Exception("Los tipos de unidades no coincide.");
			}
			if(v >= obj.v) return true;
			return false;
		};
		
		const Measure& operator = (const Measure& obj)
		{
			u = obj.u;
			v = obj.v;
			
			return *this;
		};
		const Measure& operator = (T v)
		{
			this->v = v;
			
			return *this;
		};
		operator T()const
		{
			return v;
		}

		
		void convert(const Measure& obj)
		{	
			//std::cout << " u = " << u << "\n";
			//std::cout << " Meter = " << Meter << "\n";
			switch(u)
			{
				case Unit::Feet:
					converToFeet(obj);
					break;
				case Unit::Meter:
					converToMeter(obj);
					break;
				case Unit::Inch:				
					converToInch(obj);
					break;

				case Unit::Feet2:
					converToFeet2(obj);
					break;
				case Unit::Meter2:
					converToMeter2(obj);
					break;
				case Unit::Inch2:				
					converToInch2(obj);
					break;
				
				case Unit::Pound:
					converToPound(obj);
					break;
				case Unit::Kilogram:				
					convertToKilogram(obj);
					break;

				default:
					throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};
	private:
		Unit u;
		T v;
		
		//
		void converToFeet(const Measure& obj)
		{
			switch(obj.u)
			{
				case Unit::Feet:
					v = obj.v;
					break;
				case Unit::Meter:
					v = 0.3048000097536 * obj.v;
					break;																
				case Unit::Inch:
					v = 12.000000383999999798 * obj.v;
					break;
				default:
					throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};
		void converToMeter(const Measure& obj)
		{
			switch(obj.u)
			{
				case Unit::Feet:
					v = obj.v / 3.2808399999999999785;
					break;
				case Unit::Meter:
					v = obj.v;
					break;
				case Unit::Inch:
					v = obj.v / 39.3701;
					break;
				default:
					throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};
		void converToInch(const Measure& obj)
		{
			switch(obj.u)
			{
				case Unit::Feet:
					v = 0.08333333599999999397 * obj.v;
					break;
				case Unit::Meter:
					v = 0.025400000812799999883 * obj.v;
					break;																
				case Unit::Inch:
					v = obj.v;
					break;
				default:
						throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};

		void converToFeet2(const Measure& obj)
		{
			switch(obj.u)
			{
				case Unit::Feet:
					v = obj.v;
					break;
				case Unit::Meter:
					v = 0.3048000097536 * obj.v;
					break;																
				case Unit::Inch:
					v = 12.000000383999999798 * obj.v;
					break;
				default:
					throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};
		void converToMeter2(const Measure& obj)
		{
			switch(obj.u)
			{
				case Unit::Feet:
					v = obj.v / 3.2808399999999999785;
					break;
				case Unit::Meter:
					v = obj.v;
					break;
				case Unit::Inch:
					v = obj.v / 39.3701;
					break;
				default:
					throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};
		void converToInch2(const Measure& obj)
		{
			switch(obj.u)
			{
				case Unit::Feet:
					v = 0.08333333599999999397 * obj.v;
					break;
				case Unit::Meter:
					v = 0.025400000812799999883 * obj.v;
					break;																
				case Unit::Inch:
					v = obj.v;
					break;
				default:
						throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};

		

		void converToPound(const Measure& obj)
		{
			switch(obj.u)
			{
				case Unit::Pound:
					v = obj.v;
					break;																
				case Unit::Kilogram:
					v = obj.v / 0.453592;
					break;
				default:
					throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};
		void convertToKilogram(const Measure& obj)
		{
			switch(obj.u)
			{
				default:
					throw Exception("Unidad de conversion no implemetada o desconocida",__FILE__,__LINE__);
			};
		};
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
		virtual bool check(const Point<T>& p) const = 0;
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
		Function(Domain<T>& d) : domain(&d)
		{
		};
		Function(Domain<T>* d) : domain(d)
		{
		};
		Function(short dim) : domain(NULL)
		{
		};
		
		//getter
		
		/**
		*\brief 
		*\param p toma los primero n-1 pametros y asigna el n-esimo
		**/
		virtual T operator() (Point<T>& p) = 0;

		//
		bool check(const Point<T>& p) const
		{
			if(domain) return domain->check(p);
			return true;
		};
		
	private:
		Domain<T>* domain;
	};
	
} 



#endif