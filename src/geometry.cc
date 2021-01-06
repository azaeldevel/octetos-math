
#include <math.h>
#include <iostream>


#include "geometry.hh"


namespace geometry
{







	namespace D3
	{




		
		Plane::Plane() : D2::Plane(3,'R')
		{
			
		}
		Plane::Plane(int d,char type) : D2::Plane(d,'R')
		{
			
		}
		
		//funtions
		OCTETOS_MATH_DECIMAL Plane::distance(const Point& p0,const Point& p1)
		{
			OCTETOS_MATH_DECIMAL lengx = p1[0] - p0[0];
			OCTETOS_MATH_DECIMAL lengy = p1[1] - p0[1];
			OCTETOS_MATH_DECIMAL lengz = p1[2] - p0[2];

		    OCTETOS_MATH_DECIMAL leng = pow(lengx,2) + pow(lengy,2) + pow(lengz,2)  ;

		    leng = sqrt(leng);
			
		    return leng;
		}


		



		

		//contructor
		Point::Point() : D2::Point(3,'R')
		{
			
		}
		Point::Point(int d,char type) : D2::Point(d,'R')
		{
			
		}
		Point::Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y,OCTETOS_MATH_BASEPOINT z) : D2::Point(3,'R')
		{
			at(2) = z;
		}

		//getter
		OCTETOS_MATH_BASEPOINT Point::getZ() const
		{
			return at(2);
		}

		
		//funtions
	}



	namespace D2
	{

		Plane::Plane() : core::Plane(2,'R')
		{
		}
		Plane::Plane(int d,char type) : core::Plane(d,'R')
		{
		}


		

		
		//funtions


		//contrcutor
		Point::Point() : core::Point(2,'R')
		{
		}
		Point::Point(int d,char type) : core::Point(d,'R')
		{
		}
		Point::Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y) : core::Point(2,'R')
		{
			at(0) = x;
			at(1) = y;
		}

		//operators
		Point::operator std::string() const
		{
		    std::string str = "(";
		    str += std::to_string(at(0)) ;
		    str = str + "," + std::to_string(at(1));
		    str += ")";
		    return str;
		}
		
		//getter
		OCTETOS_MATH_BASEPOINT Point::getX() const
		{
			return at(0);
		}
		OCTETOS_MATH_BASEPOINT Point::getY() const
		{
			return at(1);
		}

		
		//funtions
		OCTETOS_MATH_DECIMAL Point::distance(const Point& p) const
		{
			OCTETOS_MATH_DECIMAL lengx = p[0] - at(0);
			OCTETOS_MATH_DECIMAL lengy = p[1] - at(1);
			
			std::cout << "lengx : " << lengx << "\n";
			std::cout << "lengy : " << lengy << "\n";
			
		    OCTETOS_MATH_DECIMAL leng = pow(lengx,2) + pow(lengy,2);

		    leng = sqrt(leng);
		    return leng;
		}
		bool Point::rotate(const Point& eje)
		{
		    OCTETOS_MATH_DECIMAL lengPen = O.distance(eje);
		    if(fabs(lengPen - 1.0) > OCTETOS_MATH_EPSILON)
		    {
		        std::string msg = "El vector usado para la rotacion deve tener longitud unitaria, ahora tiene '";
		        msg = msg + std::to_string(lengPen) + "'";
		        throw octetos::core::Exception(__FILE__,__LINE__,msg);
		    }

			OCTETOS_MATH_DECIMAL v1xNew = (eje[0] * at(0)) - (eje[1] * at(1));
			OCTETOS_MATH_DECIMAL v1yNew = (eje[1] * at(0)) + (eje[0] * at(1));
			at(0) = v1xNew;
			at(1) = v1yNew;

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
			
			std::cout << "lenvect : " << (std::string)*this << "\n";
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
		
		
		
		
		
		//contructor
		Vector::Vector()
		{
		}
		Vector::Vector(const Point& e)
		{
			begin = O;
			end = e;
		}
		Vector::Vector(const Point& b,const Point& e)
		{
			begin = b;
			end = e;
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


		//operator
		Vector::operator std::string() const
		{
			std::string str = begin;
			str = str + "-->" + (std::string)end;

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
			
			return v;
		}
		Vector Vector::operator-(const Vector& obj)
		{
			Vector v;
			v.begin = begin;
			v.end[0] = end[0] - obj.end[0];
			v.end[1] = end[1] - obj.end[1];
			
			return v;
		}
		Vector Vector::operator*(OCTETOS_MATH_DECIMAL r)
		{
			Vector v;
			v.begin = begin;
			v.end[0] = end[0] * r;
			v.end[1] = end[1] * r;
			
			return v;
		}
		Vector Vector::operator/(OCTETOS_MATH_DECIMAL r)
		{
			Vector v;
			v.begin = begin;
			v.end[0] = end[0] / r;
			v.end[1] = end[1] / r;
			
			return v;
		}
	}






	namespace core
	{

		Plane::Plane(int d,char t) : std::list<Point*>(d),dimension(d), type(t)
		{
		}


		//getter
		char Plane::getType()const
		{
			return type;
		}
		const char* Plane::getTypeDescribe()const
		{
			switch(type)
			{
				case 'R':
					return "Rectangular";
				case 'C':
					return "Circular";
				default:
					return "Unknok";				
			}
		}






		
		Point::Point(const Point& obj) : std::vector<OCTETOS_MATH_BASEPOINT>(obj)
		{
	
		}
		Point::Point(int d,char t) : std::vector<OCTETOS_MATH_BASEPOINT>(d),dimension(d), type(t)
		{
		}


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
					return "Unknok";				
			}
		}


		//funtions
		const Point& Point::operator= (const Point& obj)
		{
			if(size() != obj.size()) throw octetos::core::Exception("Los objetos involucrdos en la asignacion son de difenetes tamanos",__FILE__,__LINE__);

			for(int i = 0; i < size(); i++)
			{
				at(i) = obj[i];
			}

			return *this;
		}

	}
	
} 
