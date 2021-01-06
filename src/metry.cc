
#include <math.h>
#ifdef DEBUG
	#include <iostream>
#endif

#include "metry.hh"


namespace metry
{






	Point::Point()
	{
	}
	Point::Point(const Point& obj) : 
		std::vector<OCTETOS_MATH_BASEPOINT>(obj.dimension),
		dimension(obj.dimension), type(obj.type)
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
#if OCTETOS_MATH_DIMENSION >= 3
			at(2) = obj[2];
#endif
		}

		return *this;
	}
	Point::operator std::string() const
	{
		std::string str = "(";
		str += std::to_string(at(0)) ;
		str = str + "," + std::to_string(at(1));
#if OCTETOS_MATH_DIMENSION >= 3
		str = str + "," + std::to_string(at(2));
#endif
		str += ")";
		return str;
	}
	bool Point::operator ==(const Point& obj)
	{
		if(size() != obj.size()) return false;

		if(fabs(at(0) - obj[0]) > OCTETOS_MATH_EPSILON) return false;
		if(fabs(at(1) - obj[1]) > OCTETOS_MATH_EPSILON) return false;
		if(fabs(at(2) - obj[2]) > OCTETOS_MATH_EPSILON) return false;

		return true;
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


	//funtions
	Vector Vector::orthogonal() const
	{
		Vector v;
		v.begin = begin;
		v.end[0] = end[1] * -1;
		v.end[1] = end[0];

		return v;
	}
	/**
	*\brief determina si el vector actual es paraledo al vetor pasado como paramtero
	*/
	bool Vector::isParallel(const Vector& obj) const
	{
		//se optine la pendeinte de ambos vectores y la pendiente determinada por el segmento entre ambos vectores
		//se determina como paralelo si las tres pendientes coinciden.
		
		//actual
		OCTETOS_MATH_DECIMAL dxt = end[0] - begin[0];
		OCTETOS_MATH_DECIMAL dyt = end[1] - begin[1];
		OCTETOS_MATH_DECIMAL mdxyt = dyt/dxt;
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif

		//objeto
		OCTETOS_MATH_DECIMAL dxo = obj.end[0] - obj.begin[0];
		OCTETOS_MATH_DECIMAL dyo = obj.end[1] - obj.begin[1];
		OCTETOS_MATH_DECIMAL mdxyo = dyo/dxo;
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif

		if(fabs(mdxyt - mdxyo) > OCTETOS_MATH_EPSILON) 
		{
#ifdef DEBUG
			std::cout << "La pendiente del actual " << mdxyt << " no conincide con el objetivo " << mdxyo << "\n";
#endif
			return false;//no tiene la misma pendiente
		}
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif

		//intermedio
		OCTETOS_MATH_DECIMAL dxi = end[0] - obj.begin[0];
		OCTETOS_MATH_DECIMAL dyi = end[1] - obj.begin[1];
		OCTETOS_MATH_DECIMAL mdxyi = dyi/dxi;
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif

		if(fabs(mdxyt - mdxyi) > OCTETOS_MATH_EPSILON) 
		{
#ifdef DEBUG
			std::cout << "La pendiente del actual " << mdxyt << " no conincide con el intermedio " << mdxyi << "\n";
#endif
			return false;//no tiene la misma pendiente
		}
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif
		
		return true;
	}

	
} 
