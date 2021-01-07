
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
		std::vector<OCTETOS_MATH_DECIMAL>(obj.dimension),
		dimension(obj.dimension), type(obj.type)
	{
		at(0) = obj[0];
		at(1) = obj[1];
#if OCTETOS_MATH_DIMENSION >= 3
		at(2) = obj[2];
#endif
	}
#if OCTETOS_MATH_DIMENSION == 2
	Point::Point(OCTETOS_MATH_DECIMAL x, OCTETOS_MATH_DECIMAL y) :
		std::vector<OCTETOS_MATH_DECIMAL>(2),dimension(2), type('R')
	{
		at(0) = x;
		at(1) = y;
	}
#elif OCTETOS_MATH_DIMENSION == 3
	Point::Point(OCTETOS_MATH_DECIMAL x, OCTETOS_MATH_DECIMAL y,OCTETOS_MATH_DECIMAL z) :
		std::vector<OCTETOS_MATH_DECIMAL>(3),dimension(3), type('R')
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
	OCTETOS_MATH_DECIMAL Point::getX() const
	{
		return at(0);
	}
	OCTETOS_MATH_DECIMAL Point::getY() const
	{
		return at(1);
	}
#if OCTETOS_MATH_DIMENSION >= 3
	OCTETOS_MATH_DECIMAL Point::getZ() const
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







namespace vector
{
	//constructors
	Line::Line(OCTETOS_MATH_DECIMAL b,OCTETOS_MATH_DECIMAL m): vector(Point(0.0,b),Point(1.0,m))
	{
	}
	Line::Line(const Point& p0,const Point& a) : vector(p0,a)
	{
	}
	Line::Line(const Vector& v) : vector(v)
	{
	}
	
	Point Line::getPoint(OCTETOS_MATH_DECIMAL t)const
	{
		return (vector * t).getEnd();
	}
	Vector Line::getVector(OCTETOS_MATH_DECIMAL t)const
	{
		return vector * t;
	}

	//functions
	bool Line::isParallel(const Point& p) const
	{
		Vector v(vector.getBegin(),p);
		return vector.isParallel(v);
	}
	bool Line::isOrthogonal(const Point& p) const
	{
		Vector v(vector.getBegin(),p);
		return vector.isOrthogonal(v);
	}
	bool Line::isParallel(const Line& obj) const
	{
		return vector.isParallel(obj.vector);
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


	//getter
	const Point& Vector::getBegin()const
	{
		return begin;
	}
	const Point& Vector::getEnd()const
	{
		return end;
	}
	
	//operators
	Vector::operator std::string() const
	{
		std::string str = begin;
		str = str + "->" + (std::string)end;

		return str;
	}
	OCTETOS_MATH_DECIMAL Vector::operator*(const Vector& obj)const
	{
		OCTETOS_MATH_DECIMAL v1 = end.at(0) * obj.end.at(0);
		OCTETOS_MATH_DECIMAL v2 = end.at(1) * obj.end.at(1);
			
		return v1 + v2;
	}

	Vector Vector::operator+(const Vector& obj)const
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
	Vector Vector::operator-(const Vector& obj)const
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
	Vector Vector::operator*(OCTETOS_MATH_DECIMAL r)const
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
	Vector Vector::operator/(OCTETOS_MATH_DECIMAL r)const
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
	bool Vector::normalize()
	{
		OCTETOS_MATH_DECIMAL lenvect = begin.distance(end);
        if(fabs(lenvect - OCTETOS_MATH_EPSILON) >= lenvect)
        {
            std::string msg = "El vector a normalizar deve ser diferente de 0. ahora es de '";
            msg = msg + std::to_string(lenvect) + "'";
            throw octetos::core::Exception(__FILE__,__LINE__,msg.c_str());
        }
		
        end.at(0) = end.at(0)/lenvect;
		end.at(1) = end.at(1)/lenvect;
#if OCTETOS_MATH_DIMENSION >= 3
		begin.at(2) = begin.at(2)/lenvect;
#endif

        lenvect = begin.distance(end);
        if(fabs(lenvect - 1.0) > OCTETOS_MATH_EPSILON)
        {
            std::string msg = "Despues de normalizar un vetor deveria tener longitud unitaria, ahora tiene '";
            msg = msg + std::to_string(lenvect) + "'";
            throw octetos::core::Exception(msg,__FILE__,__LINE__);
        }

        return true;
	}
	OCTETOS_MATH_DECIMAL Vector::length()const
	{
		OCTETOS_MATH_DECIMAL lengx = end[0] - begin.at(0);
		OCTETOS_MATH_DECIMAL lengy = end[1] - begin.at(1);
		OCTETOS_MATH_DECIMAL leng = pow(lengx,2) + pow(lengy,2);
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_DECIMAL lengz = end[2] - begin.at(2);
		leng += pow(lengz,2);
#endif
		leng = sqrt(leng);
		return leng;
	}	
	bool Vector::isOrthogonal(const Vector& v) const
	{
		OCTETOS_MATH_DECIMAL val = *this * v;
		if(fabs(val) > OCTETOS_MATH_EPSILON) return false;
		return true;
	}
	Vector Vector::Proj(const Vector& b)
	{
		OCTETOS_MATH_DECIMAL comp = Comp(b);
		if(fabs(b.length()- 1.0) > OCTETOS_MATH_EPSILON)
		{
			Vector u (b);
			u.normalize();
			return u * comp;
		}
		else
		{
			return b * comp;
		}
	}
	OCTETOS_MATH_DECIMAL Vector::Comp(const Vector& b)
	{
		OCTETOS_MATH_DECIMAL ps = *this * b;
		OCTETOS_MATH_DECIMAL lb = b.length();
		return ps/lb;
	}

}
} 
