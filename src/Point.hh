
#ifndef OCTETOS_MATH_POINT_HH
#define OCTETOS_MATH_POINT_HH

#include "core.hh"


namespace oct::math
{
	
	template<class T>
	class Point : protected std::vector<T>
	{
	public:
		enum Type
		{
			RECTANGULAR,
			SPHERICAL,
			NONE
		};		

	public:
		//contructor		
		Point() : type(NONE), std::vector<T>()
		{
		}	
		Point(unsigned short dimension) : type(NONE), std::vector<T>(dimension)
		{
		}	
		Point(unsigned short dimension, Type t) : type(t), std::vector<T>(dimension)
		{			
		}
		Point(const Point& obj) : std::vector<T>(obj.size())
		{
			Point<T>::at(OCTETOS_MATH_CX) = obj[OCTETOS_MATH_CX];
			Point<T>::at(OCTETOS_MATH_CY) = obj[OCTETOS_MATH_CY];
			if(getDimension() > 2) Point<T>::at(OCTETOS_MATH_CZ) = obj[OCTETOS_MATH_CZ];
			type = obj.type;
		}
		Point(T a, T  b) : type(RECTANGULAR),  std::vector<T>(2)
		{
			Point<T>::at(OCTETOS_MATH_CX) = a;
			Point<T>::at(OCTETOS_MATH_CY) = b;
		}
		Point(T a, T b, T c) : type(RECTANGULAR), std::vector<T>(3)
		{
			Point<T>::at(OCTETOS_MATH_CX) = a;
			Point<T>::at(OCTETOS_MATH_CY) = b;
			Point<T>::at(OCTETOS_MATH_CZ) = c;
		}
		Point(T a, T  b, Type t) : type(t),  std::vector<T>(2)
		{
			Point<T>::at(OCTETOS_MATH_CX) = a;
			Point<T>::at(OCTETOS_MATH_CY) = b;
		}
		Point(T a, T b, T c, Type t) : type(t), std::vector<T>(3)
		{
			Point<T>::at(OCTETOS_MATH_CX) = a;
			Point<T>::at(OCTETOS_MATH_CY) = b;
			Point<T>::at(OCTETOS_MATH_CZ) = c;
		}

		bool checkType()
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
		T getZ() const
		{
			if(Point<T>::getDimension() < 3) throw octetos::core::Exception("EL obejto no contiene coordenada Z.",__FILE__,__LINE__);
			return Point<T>::at(OCTETOS_MATH_CZ);
		}
		T getR() const//radio
		{
			if(Point<T>::getDimension() < 1) throw octetos::core::Exception("Obejto vacio",__FILE__,__LINE__);
			return Point<T>::at(OCTETOS_MATH_CX);
		}
		T getT() const//angulo thetha
		{
			if(Point<T>::getDimension() < 2) throw octetos::core::Exception("EL obejto no contiene coordenada Theta.",__FILE__,__LINE__);
			return Point<T>::at(OCTETOS_MATH_CY);
		}
		T getF() const//angulo fi
		{
			if(Point<T>::getDimension() < 3) throw octetos::core::Exception("EL obejto no contiene coordenada Fi.",__FILE__,__LINE__);
			return Point<T>::at(OCTETOS_MATH_CZ);
		}
		int getDimension()const
		{
			return Point<T>::size();
		}
		void setX(T val)
		{
			/*if(Point<T>::getDimension() == 0)
			{
				Point<T>::push_back(val);
			}
			else */if(Point<T>::getDimension() >= 1)
			{
				Point<T>::at(OCTETOS_MATH_CX) = val;
			}
			else
			{	
				std::string msg = "El tamano del areglo es ";
				msg += std::to_string(Point<T>::getDimension());
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
		}
		void setY(T val)
		{
			/*if(Point<T>::getDimension() == 0)
			{
				Point<T>::push_back(0);
				Point<T>::push_back(val);
			}
			else */if(Point<T>::getDimension() >= 2)
			{
				Point<T>::at(OCTETOS_MATH_CY) = val;
			}
			else
			{
				std::string msg = "El tamano del areglo es ";
				msg += std::to_string(Point<T>::getDimension());
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
		}

		void setZ(T val)
		{
			/*if(Point<T>::getDimension() == 0)
			{
				Point<T>::push_back(0);
				Point<T>::push_back(0);
				Point<T>::push_back(val);
			}
			else */if(Point<T>::getDimension() >= 3)
			{
				Point<T>::at(OCTETOS_MATH_CZ) = val;
			}
			else
			{
				std::string msg = "El tamano del areglo es ";
				msg += std::to_string(Point<T>::getDimension());
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
		}

		void set(T x, T y)
		{
			if(Point<T>::getDimension() < 2) Point<T>::resize(2);
			if(Point<T>::getDimension() >= 2)
			{
				Point<T>::at(OCTETOS_MATH_CX) = x;
				Point<T>::at(OCTETOS_MATH_CY) = y;
			}
			else
			{
				std::string msg = "El tamano del areglo es ";
				msg += std::to_string(Point<T>::getDimension());
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
		}
		void set(T x, T y, T z)
		{
			if(Point<T>::getDimension() < 3) Point<T>::resize(3);
			if(Point<T>::getDimension() >= 3)
			{
				Point<T>::at(OCTETOS_MATH_CX) = x;
				Point<T>::at(OCTETOS_MATH_CY) = y;
			}
			else
			{
				std::string msg = "El tamano del areglo es ";
				msg += std::to_string(Point<T>::getDimension());
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
			}
		}
		//operators
		operator std::string() const
		{
			std::string str = "(";
			str += std::to_string(Point<T>::at(OCTETOS_MATH_CX)) ;
			str = str + "," + std::to_string(Point<T>::at(OCTETOS_MATH_CY));
			if(getDimension() > 2) str = str + "," + std::to_string(Point<T>::at(OCTETOS_MATH_CZ));
			str += ")";
			return str;
		}
		const Point& operator= (const Point& obj)
		{
			if(type != obj.type) if(type != NONE) throw octetos::core::Exception("No son puntos del mismo tipo",__FILE__,__LINE__);
			if(getDimension() != obj.getDimension()) Point<T>::resize(obj.getDimension());

			Point<T>::at(OCTETOS_MATH_CX) = obj.getX();
			Point<T>::at(OCTETOS_MATH_CY) = obj.getY();
			if(getDimension() > 2) Point<T>::at(OCTETOS_MATH_CZ) = obj.getZ();

			return *this;
		}

		//operator ==
		bool operator ==(const Point<double>& obj)
		{
			if(type != obj.type) throw octetos::core::Exception("No son puntos del mismo tipo",__FILE__,__LINE__);
			if(Point<double>::size() != obj.size()) return false;

			if(fabs(Point<double>::getX() - obj.getX()) > OCTETOS_MATH_EPSILON) return false;
			if(fabs(Point<double>::getY() - obj.getY()) > OCTETOS_MATH_EPSILON) return false;
			if(getDimension() > 2) if(fabs(Point<double>::getZ() - obj.getZ()) > OCTETOS_MATH_EPSILON) return false;

			return true;
		}
		bool operator ==(const Point<float>& obj)
		{
			if(type != obj.type) throw octetos::core::Exception("No son puntos del mismo tipo",__FILE__,__LINE__);
			if(Point<float>::size() != obj.size()) return false;

			if(fabs(Point<float>::getX() - obj.getX()) > OCTETOS_MATH_EPSILON) return false;
			if(fabs(Point<float>::getY() - obj.getY()) > OCTETOS_MATH_EPSILON) return false;
			if(getDimension() > 2) if(fabs(Point<float>::getZ() - obj.getZ()) > OCTETOS_MATH_EPSILON) return false;

			return true;
		}			
		bool operator ==(const Point<long>& obj)
		{
			if(type != obj.type) throw octetos::core::Exception("No son puntos del mismo tipo",__FILE__,__LINE__);
			if(Point<long>::size() != obj.size()) return false;

			if(Point<long>::getX() != obj.getX()) return false;
			if(Point<long>::getY() != obj.getY()) return false;
			if(getDimension() > 2) if(Point<long>::getZ() != obj.getZ()) return false;

			return true;
		}	
		bool operator ==(const Point<int>& obj)
		{
			if(type != obj.type) throw octetos::core::Exception("No son puntos del mismo tipo",__FILE__,__LINE__);
			if(Point<int>::size() != obj.size()) return false;

			if(Point<int>::getX() != obj.getX()) return false;
			if(Point<int>::getY() != obj.getY()) return false;
			if(getDimension() > 2) if(Point<int>::getZ() != obj.getZ()) return false;

			return true;
		}


		//funtion
		OCTETOS_MATH_DECIMAL distance(const Point& p)const
		{
			OCTETOS_MATH_DECIMAL lengx = p[OCTETOS_MATH_CX] - Point<T>::at(OCTETOS_MATH_CX);
			OCTETOS_MATH_DECIMAL lengy = p[OCTETOS_MATH_CY] - Point<T>::at(OCTETOS_MATH_CY);
			OCTETOS_MATH_DECIMAL leng = pow(lengx,2) + pow(lengy,2);
			if(getDimension() > 2) 
			{
				OCTETOS_MATH_DECIMAL lengz = p[OCTETOS_MATH_CZ] - Point<T>::at(OCTETOS_MATH_CZ);
				leng += pow(lengz,2);
			}
			leng = sqrt(leng);
			return leng;
		}
		
	private:
		Type type;
	};
} 


#endif
