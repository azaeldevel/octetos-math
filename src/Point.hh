
#ifndef OCTETOS_MATH_POINT_HH
#define OCTETOS_MATH_POINT_HH

#include "core.hh"


namespace oct::math
{
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
} 


#endif
