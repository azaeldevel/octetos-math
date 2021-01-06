
#include <math.h>
#include <iostream>


#include "geometry.hh"


namespace geometry
{






	Point::Point()
	{
	}
	Point::Point(const Point& obj) : 
		std::vector<OCTETOS_MATH_BASEPOINT>(obj.dimension),dimension(obj.dimension), type(obj.type)
	{
		at(0) = obj[0];
		at(1) = obj[1];
#if OCTETOS_MATH_DIMENSION >= 3
		at(2) = obj[2];
#endif
	}
	Point::Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y) :
		std::vector<OCTETOS_MATH_BASEPOINT>(2),dimension(2), type('R')
	{
		at(0) = x;
		at(1) = y;
	}
#if OCTETOS_MATH_DIMENSION >= 3
	Point::Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y,OCTETOS_MATH_BASEPOINT z) :
		std::vector<OCTETOS_MATH_BASEPOINT>(3),dimension(3), type('R')
	{
		at(0) = x;
		at(1) = y;
		at(2) = z;
	}
#endif


	//getter
	char Point::getType()const
	{
		return type;
	}
	const char* Point::getTypeDescribe()const
	{
		switch(type)
		{
			case 'R':
				return "Rectangular";
			case 'C':
				return "Circular";
			default:
				return "Unknown";				
		}
	}
	OCTETOS_MATH_BASEPOINT Point::getX() const
	{
		return at(0);
	}
	OCTETOS_MATH_BASEPOINT Point::getY() const
	{
		return at(1);
	}
#if OCTETOS_MATH_DIMENSION >= 3
	OCTETOS_MATH_BASEPOINT Point::getZ() const
	{
			return at(2);
	}
#endif
		

	//funtions
	const Point& Point::operator= (const Point& obj)
	{
		if(size() == 0)
		{
			push_back(obj[0]);
			push_back(obj[1]);
			if(dimension >= 3) push_back(obj[2]);
		}
		else if(size() == obj.size())
		{
			at(0) = obj[0];
			at(1) = obj[1];
			if(dimension >= 3) at(2) = obj[2];
		}

		return *this;
	}
	Point::operator std::string() const
	{
		std::string str = "(";
		str += std::to_string(at(0)) ;
		str = str + "," + std::to_string(at(1));
		if(dimension >= 3) str = str + "," + std::to_string(at(2));
		str += ")";
		return str;
	}
	OCTETOS_MATH_DECIMAL Point::distance(const Point& p) const
	{
		OCTETOS_MATH_DECIMAL lengx = p[0] - at(0);
		OCTETOS_MATH_DECIMAL lengy = p[1] - at(1);
		OCTETOS_MATH_DECIMAL leng = pow(lengx,2) + pow(lengy,2);
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_DECIMAL lengz = p[2] - at(2);
		leng += pow(lengz,2);
#endif
		leng = sqrt(leng);
		return leng;
	}
		/*
		bool Point::rotate(const Point& eje)
		{
		    OCTETOS_MATH_DECIMAL lengPen = O.distance(eje);
		    if(fabs(lengPen - 1.0) > OCTETOS_MATH_EPSILON)
		    {
		        std::string msg = "El vector usado para la rotacion deve tener longitud unitaria, ahora tiene '";
		        msg = msg + std::to_string(lengPen) + "'";
		        throw octetos::core::Exception(msg,__FILE__,__LINE__);
		    }

			OCTETOS_MATH_DECIMAL v1xNew = (eje[0] * at(0)) - (eje[1] * at(1));
			OCTETOS_MATH_DECIMAL v1yNew = (eje[1] * at(0)) + (eje[0] * at(1));
			at(0) = v1xNew;
			at(1) = v1yNew;

		    return true;
		}
		bool Point::rotate(OCTETOS_MATH_DECIMAL theta)
		{
		    OCTETOS_MATH_DECIMAL xNew = (cos(theta) * at(0)) - (sin(theta) * at(1));
		    OCTETOS_MATH_DECIMAL yNew = (sin(theta) * at(0)) + (cos(theta) * at(1));
		    at(0) = xNew;
			at(1) = yNew;

		    return true;
		}
		bool Point::normalize()
		{
		    OCTETOS_MATH_DECIMAL lenvect = O.distance(*this);
			std::cout << "lenvect : " << lenvect << "\n";
		    if(fabs(lenvect - OCTETOS_MATH_EPSILON) >= lenvect)
		    {
		        std::string msg = "El vector a normalizar deve ser diferente de 0. ahora es de '";
		        msg = msg + std::to_string(lenvect) + "'";
		        throw octetos::core::Exception(msg,__FILE__,__LINE__);
		    }
			
			//std::cout << "lenvect : " << (std::string)*this << "\n";
		    at(0) = at(0)/lenvect;
			at(1) = at(1)/lenvect;
			
		    lenvect = O.distance(*this);
			std::cout << "lenvect : " << lenvect << "\n";
		    if(fabs(lenvect - 1.0) > OCTETOS_MATH_EPSILON)
		    {
		        std::string msg = "Despues de normalizar un vetor deveria tener longitud unitaria, ahora tiene '";
		        msg = msg + std::to_string(lenvect) + "'";
		        throw octetos::core::Exception(__FILE__,__LINE__,msg);
		    }

		    return true;
		}
		*/








	//contructors
	Vector::Vector() : begin(O), end(O)
	{
	}
	Vector::Vector(const Vector& obj) : begin(obj.begin), end(obj.end)
	{
	}
	Vector::Vector(const Point& e): begin(O),end(e)
	{
	}
	Vector::Vector(const Point& b,const Point& e): begin(b),end(e)
	{
	}

		
	//operators
	Vector::operator std::string() const
	{
		std::string str = begin;
		str = str + "->" + (std::string)end;

		return str;
	}
	OCTETOS_MATH_DECIMAL Vector::operator*(const Vector& obj)
	{
		OCTETOS_MATH_DECIMAL v1 = end.at(0) * obj.end.at(0);
		OCTETOS_MATH_DECIMAL v2 = end.at(1) * obj.end.at(1);
			
		return v1 + v2;
	}

	Vector Vector::operator+(const Vector& obj)
	{
		Vector v;
		v.begin = begin;
		v.end[0] = end[0] + obj.end[0];
		v.end[1] = end[1] + obj.end[1];
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] + obj.end[2];
#endif
		return v;
	}
	Vector Vector::operator-(const Vector& obj)
	{
		Vector v;
		v.begin = begin;
		v.end[0] = end[0] - obj.end[0];
		v.end[1] = end[1] - obj.end[1];
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] - obj.end[2];
#endif
		
		return v;
	}
	Vector Vector::operator*(OCTETOS_MATH_DECIMAL r)
	{
		Vector v;
		v.begin = begin;
		v.end[0] = end[0] * r;
		v.end[1] = end[1] * r;
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] * r;
#endif
			
		return v;
	}
	Vector Vector::operator/(OCTETOS_MATH_DECIMAL r)
	{
		Vector v;
		v.begin = begin;
		v.end[0] = end[0] / r;
		v.end[1] = end[1] / r;
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] / r;
#endif
			
		return v;
	}
	const Vector& Vector::operator= (const Vector& obj)
	{
		begin = obj.begin;
		end = obj.end;

		return *this;
	}




	
} 