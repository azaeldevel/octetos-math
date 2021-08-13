
#ifndef OCTETOS_MATH_VECTOR_HH
#define OCTETOS_MATH_VECTOR_HH

#include "Point.hh"

namespace oct::math
{


	template<class T>
	class Vector : public Point<T>
	{
	public:
		//contructor
		Vector()
		{
		}
		Vector(Index dimension): Point<T>(dimension)
		{
		}
		Vector(const Point<T>& p): Point<T>(p)
		{
		}
		Vector(T x, T y): Point<T>(x,y)
		{
		}
		Vector(T x, T y, T z): Point<T>(x,y,z)
		{
		}
		Vector(const std::vector<T*>& obj) : Point<T>(obj)
		{
		}
			
		//getter
		OCTETOS_MATH_DECIMAL operator*(const Vector& obj)const
		{
			OCTETOS_MATH_DECIMAL v1 = Vector<T>::getX() * obj.getX();
			OCTETOS_MATH_DECIMAL v2 = Vector<T>::getY() * obj.getY();
			OCTETOS_MATH_DECIMAL v = v1 + v2;
			if(Vector<T>::getDimension() > 2)
			{
				OCTETOS_MATH_DECIMAL v3 = Vector<T>::getZ() * obj.getZ();
				v += v3;
			}
			return v;
		}
		Vector operator+(const Vector& obj)const
		{
			Vector v(obj.getDimension());
			//v.begin = begin;
			v.setX(Vector<T>::getX() + obj.getX());
			v.setY(Vector<T>::getY() + obj.getY());
			if(Vector<T>::getDimension() > 2) v.setZ(Vector<T>::getZ() + obj.getZ());

			return v;
		}
		Vector operator-(const Vector& obj)const
		{
			Vector v(obj.getDimension());
			//v.begin = begin;
			v.setX(Vector<T>::getX() - obj.getX());
			v.setY(Vector<T>::getY() - obj.getY());
			if(Vector<T>::getDimension() > 2) v.setZ(Vector<T>::getZ() - obj.getZ());

			return v;
		}
		Vector operator*(T r)const
		{
			Vector v(Vector<T>::getDimension());
			//v.begin = begin;
			v.setX(Vector<T>::getX() * r);
			v.setY(Vector<T>::getY() * r);
			if(Vector<T>::getDimension() > 2) v.setZ(Vector<T>::getZ() * r);
				
			return v;
		}
		Vector operator/(T r)const
		{
			Vector v(Vector<T>::getDimension());
			//v.begin = begin;
			v.setX(Vector<T>::getX() / r);
			v.setY(Vector<T>::getY() / r);
			if(Vector<T>::getDimension() > 2) v.setZ(Vector<T>::getZ() / r);

				
			return v;
		}		

		//funtions
		Vector orthogonal() const
		{
			Vector v(Vector<T>::getDimension());
			//v.begin = begin;
			v.setX(Point<T>::getY() * T(-1));
			v.setY(Point<T>::getX());

			//if(Vector<T>::getDimension() > 2) throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);

			return v;
		}
		bool isParallel(const Vector& obj) const
		{//se comparan la pendientes de ambos vectores
			OCTETOS_MATH_DECIMAL mdyxt = fabs(Point<T>::getY()/Point<T>::getX());

			if(Vector<T>::getDimension() > 2) throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);


			//objeto
			OCTETOS_MATH_DECIMAL mdyxo = fabs(obj.getY()/obj.getX());

			if(Vector<T>::getDimension() > 2) OCTETOS_MATH_DECIMAL mdzyo = fabs(obj.getY()/obj.getZ());


			if(fabs(mdyxt - mdyxo) > OCTETOS_MATH_EPSILON) 
			{
				return false;//no tiene la misma pendiente
			}

			if(Vector<T>::getDimension() > 2) throw octetos::core::Exception("Un no es implemeteta esta fucionen 3D",__FILE__,__LINE__);
			
			return true;
		}
		bool normalize()
		{
			Point<T> O(*this);
			if(O.getDimension() == 2)
			{
				O.set(0,0);
			}
			else if(O.getDimension() == 3)
			{
				O.set(0,0,0);
			}
			OCTETOS_MATH_DECIMAL lenvect = O.distance(*this);
		    if(fabs(lenvect - OCTETOS_MATH_EPSILON) >= lenvect)
		    {
		        std::string msg = "El vector a normalizar deve ser diferente de 0. ahora es de '";
		        msg = msg + std::to_string(lenvect) + "'";
		        throw octetos::core::Exception(__FILE__,__LINE__,msg.c_str());
		    }
			
		    Point<T>::at(OCTETOS_MATH_CX) = Point<T>::at(OCTETOS_MATH_CX)/lenvect;
			Point<T>::at(OCTETOS_MATH_CY) = Point<T>::at(OCTETOS_MATH_CY)/lenvect;

			if(Vector<T>::getDimension() > 2)  Point<T>::at(OCTETOS_MATH_CZ) = Point<T>::at(OCTETOS_MATH_CZ)/lenvect;


		    lenvect = O.distance(*this);
		    if(fabs(lenvect - 1.0) > OCTETOS_MATH_EPSILON)
		    {
		        std::string msg = "Despues de normalizar un vetor deveria tener longitud unitaria, ahora tiene '";
		        msg = msg + std::to_string(lenvect) + "'";
		        throw octetos::core::Exception(msg,__FILE__,__LINE__);
		    }

		    return true;
		}
		/**
		*\brief Longitud del vector
		*/		
		OCTETOS_MATH_DECIMAL length()const
		{
			OCTETOS_MATH_DECIMAL leng = pow(Point<T>::at(OCTETOS_MATH_CX),2) + pow(Point<T>::at(OCTETOS_MATH_CY),2);
			if(Vector<T>::getDimension() > 2) leng += pow(Point<T>::at(OCTETOS_MATH_CZ),2);

			leng = sqrt(leng);
			return leng;
		}
		bool isOrthogonal(const Vector& obj) const
		{
			OCTETOS_MATH_DECIMAL val = *this * obj;
			if(fabs(val) > OCTETOS_MATH_EPSILON) return false;
			return true;
		}
		/**
		*\brief Proyeccion de a(this) en la direccion de b
		*/
		Vector Proj(const Vector& b)
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
		/**
		*\brief Component de a(this) en la direccion de b
		*/		
		OCTETOS_MATH_DECIMAL Comp(const Vector& b)
		{
			OCTETOS_MATH_DECIMAL ps = *this * b;
			OCTETOS_MATH_DECIMAL lb = b.length();
			return ps/lb;
		}

		bool isLinIndep(const Vector& v)const
		{
			return !isParallel(v);
		}
		bool isLinDep(const Vector& v)const
		{
			return isParallel(v);
		}		
		/**
		*\brief Expresa el vector actual como un combinacion lineal de los vectores a y b
		*/		
		bool combLineal(const Vector& a, const Vector& b, OCTETOS_MATH_DECIMAL& s, OCTETOS_MATH_DECIMAL& t)
		{//basado en el teorema 12.3 Pag 108
			if(!a.isLinIndep(b)) return false;
			
			Vector aortho = a.orthogonal();
			t = (aortho * *this) / (aortho * b);
			Vector bortho = b.orthogonal();
			s = (bortho * *this) / (bortho * a);

			return true;
		}

		
		bool translate(const Vector& b)
		{
			Point<T>::setX(Point<T>::getX() + b.getX());
			Point<T>::setY(Point<T>::getY() + b.getY());
			if(Vector<T>::getDimension() > 2) Point<T>::setZ(Point<T>::getZ() + b.getZ());

			return true;
		}
		bool rotate(const Vector& b)
		{
			OCTETOS_MATH_DECIMAL leng = b.length();
			if(fabs(leng - 1.0) >= OCTETOS_MATH_EPSILON)
			{
				throw octetos::core::Exception("El vector que idica la direccion deve tener longitud unitaria.",__FILE__,__LINE__);
			}
			OCTETOS_MATH_DECIMAL x = (b.getX() * Point<T>::getX()) - (b.getY() * Point<T>::getY());
			OCTETOS_MATH_DECIMAL y = (b.getY() * Point<T>::getX()) + (b.getX() * Point<T>::getY());
			Point<T>::setX(x);
			Point<T>::setY(y);

			if(Vector<T>::getDimension() > 2) throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);

			return true;
		}
		bool reflect(const Vector& b)
		{
			OCTETOS_MATH_DECIMAL leng = b.length();
			if(fabs(leng - 1.0) >= OCTETOS_MATH_EPSILON)
			{
				throw octetos::core::Exception("El vector que idica la direccion deve tener longitud unitaria.",__FILE__,__LINE__);
			}
			OCTETOS_MATH_DECIMAL x = (b.getX() * Point<T>::getX()) + (b.getY() * Point<T>::getY());
			OCTETOS_MATH_DECIMAL y = (b.getY() * Point<T>::getX()) - (b.getX() * Point<T>::getY());
			Point<T>::setX(x);
			Point<T>::setY(y);

			if(Vector<T>::getDimension() > 2) throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);

			return true;
		}
		/**
		*\brief rota(radianes) el punto this alrededor de origen
		*/
		bool rotate(OCTETOS_MATH_DECIMAL theta)
		{
			if(fabs(theta) < OCTETOS_MATH_EPSILON) return true;

			//std::cout << "sin(theta) : " << sin(theta) << "\n";
			//std::cout << "cos(theta) : " << cos(theta) << "\n";
			
			OCTETOS_MATH_DECIMAL xNew = (::cos(theta) * Point<T>::getX()) - (::sin(theta) * Point<T>::getY());
		    OCTETOS_MATH_DECIMAL yNew = (::sin(theta) * Point<T>::getX()) + (::cos(theta) * Point<T>::getY());
		    Point<T>::setX(xNew);
		    Point<T>::setY(yNew);

			return true;
		}
		/**
		*\brief cos del angulo(radian) formado por el vectora actual y el prametro b
		*/
		OCTETOS_MATH_DECIMAL cos(const Vector& b)const
		{//pag 290
			OCTETOS_MATH_DECIMAL prod = *this * b;
			OCTETOS_MATH_DECIMAL lon = length() * b.length ();
			return prod/lon;
		}
		/**
		*\brief sen del angulo(radian) formado por el vectora actual y el prametro b
		*/
		OCTETOS_MATH_DECIMAL sen(const Vector& b)const
		{//pag 290
			Vector aortho = this->orthogonal ();
			OCTETOS_MATH_DECIMAL prod = aortho * b;
			OCTETOS_MATH_DECIMAL lon = length() * b.length ();
			return prod/lon;
		}
		/**
		*\brief tan del angulo(radian) formado por el vectora actual y el prametro b
		*/
		OCTETOS_MATH_DECIMAL tan(const Vector& b)const
		{//pag 290
			Vector aortho = this->orthogonal ();
			OCTETOS_MATH_DECIMAL prod1 = aortho * b;
			OCTETOS_MATH_DECIMAL prod2 = *this * b;
			return prod1/prod2;
		}
		/**
		*\brief crea un vector de rotacion tranformado a en la direcion de b.
		*/
		Vector rotateCreate(const Vector& b)const
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
		/**
		*\brief crea un vector de angulo y longitud espoecificada.
		*/
		bool setPolar(OCTETOS_MATH_DECIMAL theta,OCTETOS_MATH_DECIMAL length)
		{
			Point<T>::setX(::cos(theta) * length);
			Point<T>::setY(::sin(theta) * length);

			if(Vector<T>::getDimension() > 2) throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);

			return true;
		}
		/**
		*\brief 
		*/
		OCTETOS_MATH_DECIMAL angle()const
		{
			OCTETOS_MATH_DECIMAL angleInRadians = std::atan2(Point<T>::getX(), Point<T>::getY());
			return (angleInRadians / M_PI) * 180.0;
		}
		OCTETOS_MATH_DECIMAL slope()const
		{
			return Point<T>::getY()/Point<T>::getX();
		}
	protected:
		
	private:
	};
} 


#endif
