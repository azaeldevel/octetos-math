
#ifndef OCTETOS_MATH_GEOMETRY_HH
#define OCTETOS_MATH_GEOMETRY_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>


//#define OCTETOS_MATH_COORDENATE int
#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_EPSILON 0.0001
#define OCTETOS_MATH_DIMENSION 2
#define OCTETOS_MATH_CX 0
#define OCTETOS_MATH_CY 1
#define OCTETOS_MATH_CZ 2


namespace metry
{
namespace core
{
	template<class T>
	class Point : public std::vector<T>
	{
	public:
		Point() : std::vector<T>()
		{
		}
		Point(int dimension) : std::vector<T>(dimension)
		{
		}
	};
}

namespace rect
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
			return Point<T>::at(OCTETOS_MATH_CX);
		}
		T getY() const
		{
			return Point<T>::at(OCTETOS_MATH_CY);
		}
#if OCTETOS_MATH_DIMENSION >= 3
		T getZ() const
		{
			return Point<T>::at(OCTETOS_MATH_CZ);
		}
#endif
		int getDimension()const
		{
			return Point<T>::size();
		}
		void setX(T val)
		{
			Point<T>::at(OCTETOS_MATH_CX) = val;
		}
		void setY(T val)
		{
			Point<T>::at(OCTETOS_MATH_CY) = val;
		}
		void setZ(T val)
		{
			Point<T>::at(OCTETOS_MATH_CZ) = val;
		}
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



	template<class T>
	class Vector : public Point<T>
	{
	public:
		//contructor
		Vector(): Point<T>()
		{
		}
		Vector(short dimension): Point<T>(dimension)
		{
		}
		Vector(const Point<T>& p): Point<T>(p)
		{
		}
		Vector(T x, T y): Point<T>(x,y)
		{
		}
#if OCTETOS_MATH_DIMENSION >= 3
		Vector(T x, T y, T z): Point<T>(x,y,z)
		{
		}
#endif
			
		//getter
			
		//operator
		//operator std::string() const;
		OCTETOS_MATH_DECIMAL operator*(const Vector& obj)const
		{
			OCTETOS_MATH_DECIMAL v1 = Vector<T>::getX() * obj.getX();
			OCTETOS_MATH_DECIMAL v2 = Vector<T>::getY() * obj.getY();
			OCTETOS_MATH_DECIMAL v = v1 + v2;
#if OCTETOS_MATH_DIMENSION >= 3
			OCTETOS_MATH_DECIMAL v3 = Vector<T>::getZ() * obj.getZ();
			v += v3;
#endif
			return v;
		}
		Vector operator+(const Vector& obj)const
		{
			Vector v;
			//v.begin = begin;
			v.push_back(Vector<T>::getX() + obj.getX());
			v.push_back(Vector<T>::getY() + obj.getY());
#if OCTETOS_MATH_DIMENSION >= 3
			v.push_back(Vector<T>::getZ() + obj.getZ());
#endif
			return v;
		}
		Vector operator-(const Vector& obj)const
		{
			Vector v;
			//v.begin = begin;
			v.push_back(Vector<T>::getX() - obj.getX());
			v.push_back(Vector<T>::getY() - obj.getY());
#if OCTETOS_MATH_DIMENSION >= 3
			v.push_back(Vector<T>::getZ() - obj.getZ());
#endif
			return v;
		}
		Vector operator*(T r)const
		{
			Vector v;
			//v.begin = begin;
			v.push_back(Vector<T>::getX() * r);
			v.push_back(Vector<T>::getY() * r);
#if OCTETOS_MATH_DIMENSION >= 3
			v.push_back(Vector<T>::getZ() * r);
#endif
				
			return v;
		}
		Vector operator/(T r)const
		{
			Vector v;
			//v.begin = begin;
			v.push_back(Vector<T>::getX() / r);
			v.push_back(Vector<T>::getY() / r);
#if OCTETOS_MATH_DIMENSION >= 3
			v.push_back(Vector<T>::getZ() / r);
#endif
				
			return v;
		}		

		//funtions
		Vector orthogonal() const
		{
			Vector v;
			//v.begin = begin;
			v.push_back(Point<T>::getY() * -1);
			v.push_back(Point<T>::getX());
	#if OCTETOS_MATH_DIMENSION >= 3
			throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
	#endif
			return v;
		}
		bool isParallel(const Vector& obj) const
		{//se comparan la pendientes de ambos vectores
			
			OCTETOS_MATH_DECIMAL mdyxt = fabs(Point<T>::getY()/Point<T>::getX());
#if OCTETOS_MATH_DIMENSION >= 3
			throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
#endif

			//objeto
			OCTETOS_MATH_DECIMAL mdyxo = fabs(obj.getY()/obj.getX());
#if OCTETOS_MATH_DIMENSION >= 3
			OCTETOS_MATH_DECIMAL mdzyo = fabs(obj.getY()/obj.getZ());
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
		bool normalize()
		{
			Point<T> O(*this);
			if(O.getDimension() == 2)
			{
				O[0] = 0.0;
				O[1] = 0.0;
			}
			else if(O.getDimension() == 3)
			{
				O[0] = 0.0;
				O[1] = 0.0;
				O[2] = 0.0;
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
#if OCTETOS_MATH_DIMENSION >= 3
			Point<T>::at(OCTETOS_MATH_CZ) = Point<T>::at(OCTETOS_MATH_CZ)/lenvect;
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
		/**
		*\brief Longitud del vector
		*/		
		OCTETOS_MATH_DECIMAL length()const
		{
			OCTETOS_MATH_DECIMAL leng = pow(Point<T>::at(OCTETOS_MATH_CX),2) + pow(Point<T>::at(OCTETOS_MATH_CY),2);
#if OCTETOS_MATH_DIMENSION >= 3
			leng += pow(Point<T>::at(OCTETOS_MATH_CZ),2);
#endif
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
	#if OCTETOS_MATH_DIMENSION >= 3
			Point<T>::setZ(Point<T>::getZ() + b.getZ());
	#endif

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
	#if OCTETOS_MATH_DIMENSION >= 3
			throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
	#endif
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
	#if OCTETOS_MATH_DIMENSION >= 3
			throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
	#endif
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
	#if OCTETOS_MATH_DIMENSION >= 3
			throw octetos::core::Exception("Aun no esta implemeteda esta funcion en 3D",__FILE__,__LINE__);
	#endif
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

	template<class T>
	class Line
	{
	public:
		//constructor
		Line()
		{}
		Line(const Vector<T>& pp0,const Vector<T>& p1) : p0(pp0)
		{
			Vector<T> v = p1 - p0;
			v.normalize();
			a = v;
			m = a.slope();
		}
		Line(OCTETOS_MATH_DECIMAL b, OCTETOS_MATH_DECIMAL m) : p0(0.0,b),a(1.0,m)	
		{
			this->m = m;
		}
		Line(const Vector<T>& v) : p0(Point<T>(v.p0)),a(Point<T>(v.a))
		{
		}

		//operator
		operator std::string() const
		{
			std::string str = "L={";
			str += (std::string)p0 + " + t" + (std::string)a + " | para todo t ϵ R}";
			return (std::string)str;
		}
		
		//

		//
		bool isParallel(const Vector<T>& obj) const
		{
			return isParallel(obj);
		}
		bool isOrthogonal(const Vector<T>& obj) const
		{
			return isOrthogonal(obj);
		}
		bool isParallel(const Line& obj) const
		{
			return a.isParallel(obj.a);
		}
		bool isOrthogonal(const Line& obj) const
		{
			return a.isOrthogonal(obj.a);
		}
		OCTETOS_MATH_DECIMAL distance(const Vector<T>& p) const
		{	
			//pagina 42
			Vector<T> vQ = p - p0;
			Vector<T> n = a.orthogonal();
			return fabs(vQ.Comp(n));
		}
		OCTETOS_MATH_DECIMAL onX(T x)const
		{
			return (m * x) + p0[1];
		}
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_DECIMAL onXY(OCTETOS_MATH_COORDENATE x,OCTETOS_MATH_COORDENATE y)const;
#endif
		Line orthogonalOn(const Vector<T>& p0)const
		{
			Vector<T> n = a.orthogonal();
			Line l;
			l.p0 = p0;
			l.a = n;
			return l;
		}


		OCTETOS_MATH_DECIMAL angle(const Line&)const;
		OCTETOS_MATH_DECIMAL angle()const;
	private:
		Vector<T> p0;
		Vector<T> a;
		OCTETOS_MATH_DECIMAL m;
	};

}
} 


#endif 