
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
	Line::Line(OCTETOS_MATH_DECIMAL b,OCTETOS_MATH_DECIMAL m): p0(0.0,b),a(1.0,m)
	{
	}
	Line::Line(const Vector& pp0,const Vector& pp1) : p0(pp0)
	{
		Vector v = pp1 - pp0;
		v.normalize();
		a = v;
	}
	/*
	Line::Line(const Vector& v) : : p0(Point(v.p0)),a(Point(v.a))
	{
	}
	*/
	//operator
	Line::operator std::string() const
	{
		std::string str = "L={";
		str += (std::string)p0 + " + t" + (std::string)a + " | para t pertecen a R}";
		return (std::string)str;
	}
	
	Point Line::getPoint(OCTETOS_MATH_DECIMAL t)const
	{
		Vector v = a * t;
		v = v + p0;
		return v;
	}
	/*
	Vector Line::getVector(OCTETOS_MATH_DECIMAL t)const
	{
		return vector * t;
	}
	*/
	//functions
	bool Line::isParallel(const Point& p) const
	{
		Vector v(p);
		return isParallel(v);
	}
	bool Line::isOrthogonal(const Point& p) const
	{
		Vector v(p);
		return isOrthogonal(v);
	}
	bool Line::isParallel(const Line& obj) const
	{
		return a.isParallel(obj.a);
	}
	/*
	Vector Line::orthogonalIn(const Point& p) const
	{
		//es punto es paralelo a la recta?
		bool isp = isParallel(p);
		if(isp)
		{
			//OCTETOS_MATH_DECIMAL sx = p.getX() - vector.getBegin().getX();
			//sx = sx/vector.getEnd().getX();
			Vector vp(p,vector.getEnd());
			return vp.orthogonal();
		}
		else
		{
			return Vector(O,O);
		}
	}
	*/
	OCTETOS_MATH_DECIMAL Line::distance(const Vector& p) const
	{	
		//pagina 42
		Vector vQ = p - p0;
		//std::cout << "a" << (std::string)a << "\n";
		Vector n = a.orthogonal();
		//std::cout << "n" << (std::string)n << "\n";
		//std::cout << "vQ:" << (std::string)vQ << "\n";
		return fabs(vQ.Comp(n));
	}




	
	//contructors
	Vector::Vector() : Point(O)
	{
	}
	Vector::Vector(const Vector& obj) : Point(obj)
	{
	}
	Vector::Vector(const Point& e): Point(e)
	{
	}	
	/*
	Vector::Vector(const Point& b,const Point& e): begin(b)
	{
		end[0] =  b[0] - e[0];
		end[1] =  b[1] - e[1];
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif
	}
	*/
#if OCTETOS_MATH_DIMENSION == 2
	Vector::Vector(OCTETOS_MATH_DECIMAL x, OCTETOS_MATH_DECIMAL y) : Point(x,y)
	{
		at(0) = x;
		at(1) = y;
	}
#elif OCTETOS_MATH_DIMENSION == 3
	Vector::Vector(OCTETOS_MATH_DECIMAL x, OCTETOS_MATH_DECIMAL y,OCTETOS_MATH_DECIMAL z) : Point(x,y,z)
	{
		at(0) = x;
		at(1) = y;
		at(2) = z;
	}
#endif

	//getter
	/*
	const Point& Vector::getBegin()const
	{
		return begin;
	}
	const Point& Vector::getEnd()const
	{
		return end;
	}
	*/
	
	//operators
	Vector::operator std::string() const
	{
		return Point::operator std::string();
	}
	OCTETOS_MATH_DECIMAL Vector::operator*(const Vector& obj)const
	{
		OCTETOS_MATH_DECIMAL v1 = at(0) * obj.at(0);
		OCTETOS_MATH_DECIMAL v2 = at(1) * obj.at(1);
		OCTETOS_MATH_DECIMAL v = v1 + v2;
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif
		return v;
	}

	Vector Vector::operator+(const Vector& obj)const
	{
		Vector v;
		//v.begin = begin;
		v[0] = at(0) + obj[0];
		v[1] = at(1) + obj[1];
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] + obj.end[2];
#endif
		return v;
	}
	Vector Vector::operator-(const Vector& obj)const
	{
		Vector v;
		//v.begin = begin;
		v[0] = at(0) - obj[0];
		v[1] = at(1) - obj[1];
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] - obj.end[2];
#endif
		
		return v;
	}
	Vector Vector::operator*(OCTETOS_MATH_DECIMAL r)const
	{
		Vector v;
		//v.begin = begin;
		v[0] = at(0) * r;
		v[1] = at(1) * r;
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] * r;
#endif
			
		return v;
	}
	Vector Vector::operator/(OCTETOS_MATH_DECIMAL r)const
	{
		Vector v;
		//v.begin = begin;
		v[0] = at(0) / r;
		v[1] = at(1) / r;
#if OCTETOS_MATH_DIMENSION >= 3
		v.end[2] = end[2] / r;
#endif
			
		return v;
	}
	const Vector& Vector::operator= (const Vector& obj)
	{
		return Point::operator =(obj);
	}


	//funtions
	Vector Vector::orthogonal() const
	{
		Vector v;
		//v.begin = begin;
		v[0] = at(1) * -1;
		v[1] = at(0);

		return v;
	}
	/**
	*\brief determina si el vector actual es paraledo al vetor pasado como paramtero
	*/
	bool Vector::isParallel(const Vector& obj) const
	{//se comparan la pendientes de ambos vectores
		
		//actual
		//OCTETOS_MATH_DECIMAL dxt = end[0] - begin[0];
		//OCTETOS_MATH_DECIMAL dyt = end[1] - begin[1];
		OCTETOS_MATH_DECIMAL mdxyt = at(1)/at(0);
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif

		//objeto
		//OCTETOS_MATH_DECIMAL dxo = obj.end[0] - obj.begin[0];
		//OCTETOS_MATH_DECIMAL dyo = obj.end[1] - obj.begin[1];
		OCTETOS_MATH_DECIMAL mdxyo = obj[1]/obj[0];
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif

		if(fabs(mdxyt - mdxyo) > OCTETOS_MATH_EPSILON) 
		{
			return false;//no tiene la misma pendiente
		}
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Incompleto",__FILE__,__LINE__);
#endif
		
		return true;
	}
	bool Vector::normalize()
	{
		OCTETOS_MATH_DECIMAL lenvect = O.distance(*this);
        if(fabs(lenvect - OCTETOS_MATH_EPSILON) >= lenvect)
        {
            std::string msg = "El vector a normalizar deve ser diferente de 0. ahora es de '";
            msg = msg + std::to_string(lenvect) + "'";
            throw octetos::core::Exception(__FILE__,__LINE__,msg.c_str());
        }
		
        at(0) = at(0)/lenvect;
		at(1) = at(1)/lenvect;
#if OCTETOS_MATH_DIMENSION >= 3
		end.at(2) = end.at(2)/lenvect;
#endif

        lenvect = O.distance(*this);
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
		//OCTETOS_MATH_DECIMAL lengx = end[0] - begin.at(0);
		//OCTETOS_MATH_DECIMAL lengy = end[1] - begin.at(1);
		OCTETOS_MATH_DECIMAL leng = pow(at(0),2) + pow(at(1),2);
#if OCTETOS_MATH_DIMENSION >= 3
		//OCTETOS_MATH_DECIMAL lengz = end[2] - begin.at(2);
		leng += pow(end[2],2);
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
	bool Vector::isNull()const
	{
		//if(begin.getX() > OCTETOS_MATH_EPSILON) return false;
		//if(begin.getY() > OCTETOS_MATH_EPSILON) return false;
		if(at(0) > OCTETOS_MATH_EPSILON) return false;
		if(at(1) > OCTETOS_MATH_EPSILON) return false;
#if OCTETOS_MATH_DIMENSION >= 3
		if(at(2) > OCTETOS_MATH_EPSILON) return false;
#endif
		return true;
	}

}
} 
