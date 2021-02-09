
#ifndef OCTETOS_MATH_POINT_HH
#define OCTETOS_MATH_POINT_HH

#include <core.hh>


#define OCTETOS_MATH_CX 0
#define OCTETOS_MATH_CY 1
#define OCTETOS_MATH_CZ 2


namespace metry::rect
{
	template<class T>
	class Point : public core::Point<T>
	{
	public:
		//contructor		
		Point() : core::Point<T>()
		{
		}
		Point(const Point& obj) : core::Point<T>(obj.size())
		{
			Point<T>::at(OCTETOS_MATH_CX) = obj[OCTETOS_MATH_CX];
			Point<T>::at(OCTETOS_MATH_CY) = obj[OCTETOS_MATH_CY];
#if OCTETOS_MATH_DIMENSION >= 3
			Point<T>::at(OCTETOS_MATH_CZ) = obj[OCTETOS_MATH_CZ];
#endif
		}
		Point(T x, T y) : core::Point<T>(2)
		{
			Point<T>::at(OCTETOS_MATH_CX) = x;
			Point<T>::at(OCTETOS_MATH_CY) = y;
	#if OCTETOS_MATH_DIMENSION >= 3
			Point<T>::at(OCTETOS_MATH_CZ) = 0.0;
	#endif
		}
#if OCTETOS_MATH_DIMENSION >= 3
		Point(T x, T y, T z) : core::Point<T>(3)
		{
			Point<T>::at(OCTETOS_MATH_CX) = x;
			Point<T>::at(OCTETOS_MATH_CY) = y;
			Point<T>::at(OCTETOS_MATH_CZ) = z;
		}
#endif
		
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
				Point<T>::at(OCTETOS_MATH_CX) = obj[OCTETOS_MATH_CX];
				Point<T>::at(OCTETOS_MATH_CY) = obj[OCTETOS_MATH_CY];
#if OCTETOS_MATH_DIMENSION >= 3
				Point<T>::at(OCTETOS_MATH_CZ) = obj[OCTETOS_MATH_CZ];
#endif
			}
			else
			{

			}

			return *this;
		}
		bool operator ==(const Point<double>& obj)
		{
			if(Point<double>::size() != obj.size()) return false;

			if(fabs(Point<double>::at(OCTETOS_MATH_CX) - obj[OCTETOS_MATH_CX]) > OCTETOS_MATH_EPSILON) return false;
			if(fabs(Point<double>::at(OCTETOS_MATH_CY) - obj[OCTETOS_MATH_CY]) > OCTETOS_MATH_EPSILON) return false;
			if(fabs(Point<double>::at(OCTETOS_MATH_CZ) - obj[OCTETOS_MATH_CZ]) > OCTETOS_MATH_EPSILON) return false;

			return true;
		}		
		bool operator ==(const Point<int>& obj)
		{
			if(Point<int>::size() != obj.size()) return false;

			if(Point<int>::at(OCTETOS_MATH_CX) = obj[OCTETOS_MATH_CX]) return false;
			if(Point<int>::at(OCTETOS_MATH_CY) = obj[OCTETOS_MATH_CY]) return false;
			if(Point<int>::at(OCTETOS_MATH_CZ) = obj[OCTETOS_MATH_CZ]) return false;

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
} 


#endif
