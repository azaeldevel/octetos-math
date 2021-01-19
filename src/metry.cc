
#include <math.h>
#include <cmath>
#ifdef DEBUG
	#include <iostream>
#endif

#include "metry.hh"


#define CX 0
#define CY 1
#define CZ 2

namespace metry
{



namespace core
{

	Point::Point(int dimension) : std::vector<OCTETOS_MATH_COORDENATE>(dimension)
	{
	}

}


namespace rect
{
	Point::Point() : core::Point(OCTETOS_MATH_DIMENSION)
	{
	}
	Point::Point(const Point& obj) : core::Point(obj.getDimension())
	{
		at(0) = obj[0];
		at(1) = obj[1];
#if OCTETOS_MATH_DIMENSION >= 3
		at(2) = obj[2];
#endif
	}
	Point::Point(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y) : core::Point(OCTETOS_MATH_DIMENSION)
	{
		at(0) = x;
		at(1) = y;
#if OCTETOS_MATH_DIMENSION >= 3
		at(2) = 0.0;
#endif
	}
#if OCTETOS_MATH_DIMENSION >= 3
	Point::Point(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y,OCTETOS_MATH_COORDENATE z) : core::Point(OCTETOS_MATH_DIMENSION)
	{
		at(0) = x;
		at(1) = y;
		at(2) = z;
	}
#endif


	//getter	
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
	int Point::getDimension()const
	{
		return OCTETOS_MATH_DIMENSION;
	}

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
	
	/**/







	




	
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
	

	Vector::Vector(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y) : Point(x,y)
	{

	}
#if OCTETOS_MATH_DIMENSION >= 3
	Vector::Vector(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y,OCTETOS_MATH_COORDENATE z) : Point(x,y,z)
	{
	}
#endif

	//getter
	
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
		OCTETOS_MATH_DECIMAL v3 = at(2) * obj.at(2);
		v += v3;
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
		v[2] = at(2) + obj[2];
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
		v[2] = at(2) - obj[2];
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
		v[2] = at(2) * r;
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
		v[2] = at(2) / r;
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
#if OCTETOS_MATH_DIMENSION >= 3
		
#endif
		return v;
	}
	/**
	*\brief determina si el vector actual es paraledo al vetor pasado como paramtero
	*/
	bool Vector::isParallel(const Vector& obj) const
	{//se comparan la pendientes de ambos vectores
		
		OCTETOS_MATH_DECIMAL mdyxt = fabs(at(1)/at(0));
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
#endif

		//objeto
		OCTETOS_MATH_DECIMAL mdyxo = fabs(obj[1]/obj[0]);
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_DECIMAL mdzyo = fabs(obj[1]/obj[2]);
#endif

		if(fabs(mdyxt - mdyxo) > OCTETOS_MATH_EPSILON) 
		{
			return false;//no tiene la misma pendiente
		}
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Un no es implemeteta esta fucionen 3D",__FILE__,__LINE__);
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
		at(2) = at(2)/lenvect;
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
		OCTETOS_MATH_DECIMAL leng = pow(at(0),2) + pow(at(1),2);
#if OCTETOS_MATH_DIMENSION >= 3
		leng += pow(at(2),2);
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
	/*
	bool Vector::isNull()const
	{
		if(at(0) > OCTETOS_MATH_EPSILON) return false;
		if(at(1) > OCTETOS_MATH_EPSILON) return false;
#if OCTETOS_MATH_DIMENSION >= 3
		if(at(2) > OCTETOS_MATH_EPSILON) return false;
#endif
		return true;
	}
	*/
	OCTETOS_MATH_DECIMAL Vector::slope()const
	{
		return at(1)/at(0);
	}

	bool Vector::isLinIndep(const Vector& v)const
	{
		return !isParallel(v);
	}
	bool Vector::isLinDep(const Vector& v)const
	{
		return isParallel(v);
	}
	bool Vector::combLineal(const Vector& a, const Vector& b,OCTETOS_MATH_DECIMAL& s, OCTETOS_MATH_DECIMAL& t)
	{//basado en el teorema 12.3 Pag 108
		if(!a.isLinIndep(b)) return false;
		
		Vector aortho = a.orthogonal();
		t = (aortho * *this) / (aortho * b);
		Vector bortho = b.orthogonal();
		s = (bortho * *this) / (bortho * a);

		return true;
	}
	bool Vector::translate(const Vector& b)
	{
		at(CX) = at(CX) + b[CX];
		at(CY) = at(CY) + b[CY];
#if OCTETOS_MATH_DIMENSION >= 3
		at(CZ) = at(CZ) + a[CZ];
#endif

		return true;
	}
	bool Vector::rotate(const Vector& b)
	{
		OCTETOS_MATH_DECIMAL leng = b.length();
		if(fabs(leng - 1.0) >= OCTETOS_MATH_EPSILON)
		{
			throw octetos::core::Exception("El vector que idica la direccion deve tener longitud unitaria.",__FILE__,__LINE__);
		}
		OCTETOS_MATH_DECIMAL x = (b[CX] * at(CX)) - (b[CY] * at(CY));
		OCTETOS_MATH_DECIMAL y = (b[CY] * at(CX)) + (b[CX] * at(CY));
		at(CX) = x;
		at(CY) = y;
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
#endif
		return true;
	}
	
	bool Vector::reflect(const Vector& b)
	{
		OCTETOS_MATH_DECIMAL leng = b.length();
		if(fabs(leng - 1.0) >= OCTETOS_MATH_EPSILON)
		{
			throw octetos::core::Exception("El vecto que idica la direccion deve tener longitud unitaria.",__FILE__,__LINE__);
		}
		OCTETOS_MATH_DECIMAL x = (b[CX] * at(CX)) + (b[CY] * at(CY));
		OCTETOS_MATH_DECIMAL y = (b[CY] * at(CX)) - (b[CX] * at(CY));
		at(CX) = x;
		at(CY) = y;
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
#endif
		return true;
	}
	bool Vector::rotate(OCTETOS_MATH_DECIMAL theta)
	{
		if(fabs(theta) < OCTETOS_MATH_EPSILON) return true;

		//std::cout << "sin(theta) : " << sin(theta) << "\n";
		//std::cout << "cos(theta) : " << cos(theta) << "\n";
		
		OCTETOS_MATH_DECIMAL xNew = (::cos(theta) * at(CX)) - (::sin(theta) * at(CY));
        OCTETOS_MATH_DECIMAL yNew = (::sin(theta) * at(CX)) + (::cos(theta) * at(CY));
        at(CX) = xNew;
        at(CY) = yNew;

		return true;
	}
	OCTETOS_MATH_DECIMAL Vector::cos(const Vector& b)const
	{//pag 290
		OCTETOS_MATH_DECIMAL prod = *this * b;
		OCTETOS_MATH_DECIMAL lon = length() * b.length ();
		return prod/lon;
	}
	OCTETOS_MATH_DECIMAL Vector::sen(const Vector& b)const
	{//pag 290
		Vector aortho = this->orthogonal ();
		OCTETOS_MATH_DECIMAL prod = aortho * b;
		OCTETOS_MATH_DECIMAL lon = length() * b.length ();
		return prod/lon;
	}
	OCTETOS_MATH_DECIMAL Vector::tan(const Vector& b)const
	{//pag 290
		Vector aortho = this->orthogonal ();
		OCTETOS_MATH_DECIMAL prod1 = aortho * b;
		OCTETOS_MATH_DECIMAL prod2 = *this * b;
		return prod1/prod2;
	}
	Vector Vector::rotateCreate(const Vector& b)const
	{
		//pag 285
		OCTETOS_MATH_DECIMAL prod1 = *this * b;
		OCTETOS_MATH_DECIMAL lon1 = length() * b.length ();
		
		Vector aortho = this->orthogonal ();
		OCTETOS_MATH_DECIMAL prod2 = aortho * b;
		OCTETOS_MATH_DECIMAL lon2 = length() * b.length ();

		Vector u(prod1/lon1,prod2/lon2);
		return u;
	}
	/*bool Vector::set(OCTETOS_MATH_DECIMAL theta,OCTETOS_MATH_DECIMAL length = 1.0)
	{
		at(CX) = cos(theta) * length;
		at(CY) = sen(theta) * length;
#if OCTETOS_MATH_DIMENSION >= 3
		throw octetos::core::Exception("Aun no esta implemeteda esta funcion 3D",__FILE__,__LINE__);
#endif
		return true;
	}*/
	OCTETOS_MATH_DECIMAL Vector::angle()const
	{
		OCTETOS_MATH_DECIMAL angleInRadians = std::atan2(at(CX), at(CY));
		return (angleInRadians / M_PI) * 180.0;
	}

	//constructors
	Line::Line()
	{
	}
	Line::Line(OCTETOS_MATH_DECIMAL b,OCTETOS_MATH_DECIMAL m): p0(0.0,b),a(1.0,m)
	{
		this->m = m;
	}
	Line::Line(const Vector& pp0,const Vector& pp1) : p0(pp0)
	{
		Vector v = pp1 - pp0;
		v.normalize();
		a = v;
		m = a.slope();
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
		str += (std::string)p0 + " + t" + (std::string)a + " | para todo t ϵ R}";
		return (std::string)str;
	}
	
		
	//functions
	bool Line::isParallel(const Vector& v) const
	{
		return isParallel(v);
	}
	bool Line::isOrthogonal(const Vector& v) const
	{
		return isOrthogonal(v);
	}
	bool Line::isParallel(const Line& obj) const
	{
		return a.isParallel(obj.a);
	}
	bool Line::isOrthogonal(const Line& l2) const
	{
		return a.isOrthogonal(l2.a);
	}
	OCTETOS_MATH_DECIMAL Line::distance(const Vector& p) const
	{	
		//pagina 42
		Vector vQ = p - p0;
		Vector n = a.orthogonal();
		return fabs(vQ.Comp(n));
	}
	OCTETOS_MATH_DECIMAL Line::onX(OCTETOS_MATH_COORDENATE x)const
	{
		return (m * x) + p0[1];
	}
	Line Line::orthogonalOn(const Vector& p0)const
	{
		Vector n = a.orthogonal();
		Line l;
		l.p0 = p0;
		l.a = n;
		return l;
	}
	OCTETOS_MATH_COORDENATE Line::angle(const Line& l2)const
	{
		if(isParallel(l2))
		{
			throw octetos::core::Exception("Esta tratando determinar en angulo entre rectas paralelas.",__FILE__,__LINE__);
		}
		else if(isOrthogonal(l2))
		{
			return 90.0;
		}

		OCTETOS_MATH_COORDENATE l1Theta = a.angle();
		OCTETOS_MATH_COORDENATE l2Theta = l2.angle();

		if(l1Theta > 0 and l2Theta > 0)
		{
			return l1Theta - l2Theta;
		}
		else if((l1Theta > 0 and l2Theta < 0) or (l1Theta < 0 and l2Theta > 0))
		{
			Vector orthoa = a.orthogonal ();
			OCTETOS_MATH_COORDENATE v1 = orthoa * l2.a;
			OCTETOS_MATH_COORDENATE v2 = a * l2.a;
			return v1/v2;
		}
		else
		{
			throw octetos::core::Exception("Angulo entre rectas no determinable.",__FILE__,__LINE__);
		}
	}
	OCTETOS_MATH_DECIMAL Line::angle()const
	{
		return a.angle();
	}







	Circumference::Circumference(OCTETOS_MATH_DECIMAL r) : radio2(pow(r,2))
	{
	}

	//funtions
	OCTETOS_MATH_DECIMAL Circumference::onX(OCTETOS_MATH_COORDENATE x)const
	{
		OCTETOS_MATH_DECIMAL y = pow(radio2,2) - radio2;
		return sqrt(y);
	}




	Parable::Parable(OCTETOS_MATH_DECIMAL p) : p4(4 * p)
	{
	}
	OCTETOS_MATH_DECIMAL Parable::onX(OCTETOS_MATH_COORDENATE x)const
	{
		return sqrt(p4*x);
	}


	Ellipse::Ellipse(OCTETOS_MATH_DECIMAL a,OCTETOS_MATH_DECIMAL b) : a2(pow(a,2)), b2(pow(b,2))
	{
		
	}

	OCTETOS_MATH_DECIMAL Ellipse::onX(OCTETOS_MATH_COORDENATE x)const
	{
		return (b2-(b2*pow(x,2)/a2));
	}




	
	Hyperbola::Hyperbola(OCTETOS_MATH_DECIMAL a,OCTETOS_MATH_DECIMAL b) : a2(pow(a,2)), b2(pow(b,2))
	{
		
	}

	OCTETOS_MATH_DECIMAL Hyperbola::onX(OCTETOS_MATH_COORDENATE x)const
	{
		return (b2+(b2*pow(x,2)/a2));
	}
}
} 
