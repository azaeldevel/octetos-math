
#ifndef OCTETOS_MATH_GEOMETRY_HH
#define OCTETOS_MATH_GEOMETRY_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>


#define OCTETOS_MATH_COORDENATE double
#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_EPSILON 0.0001
#define OCTETOS_MATH_DIMENSION 2



namespace metry
{
namespace core
{
	class Point : public std::vector<OCTETOS_MATH_COORDENATE>
	{
	public:
		Point(int dimension);
	};
}

namespace rect
{
	class Point : public core::Point
	{
	public:
		//contructor
		Point();
		Point(const Point& obj);

		Point(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y);
#if OCTETOS_MATH_DIMENSION >= 3
		Point(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y, OCTETOS_MATH_COORDENATE z);
#endif
		
		//getter
		OCTETOS_MATH_DECIMAL getX() const;
		OCTETOS_MATH_DECIMAL getY() const;
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_DECIMAL getZ() const;
#endif
		int getDimension()const;
		
		//operators
		operator std::string() const;
		const Point& operator= (const Point&);
		bool operator ==(const Point&);
		
		//funtion
		OCTETOS_MATH_DECIMAL distance(const Point& p)const;
		
	private:
		int dimension;
	};

#if OCTETOS_MATH_DIMENSION == 2
	static const Point O(0.0,0.0);
#elif OCTETOS_MATH_DIMENSION == 3
	static const Point O(0.0,0.0,0.0);
#else
	#error "Agrege un valor para 'OCTETOS_MATH_DIMENSION'"
#endif
	
	class Vector : public Point
	{
	public:
		//contructor
		Vector();
		Vector(const Point& end);
		Vector(const Vector&);

		Vector(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y);
#if OCTETOS_MATH_DIMENSION >= 3
		Vector(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y, OCTETOS_MATH_COORDENATE z);
#endif
			
		//getter
			
		//operator
		operator std::string() const;
		OCTETOS_MATH_DECIMAL operator*(const Vector&)const;
		Vector operator+(const Vector&)const;
		Vector operator-(const Vector&)const;
		Vector operator*(OCTETOS_MATH_DECIMAL)const;
		Vector operator/(OCTETOS_MATH_DECIMAL)const;
		const Vector& operator= (const Vector&);

		//funtions
		Vector orthogonal() const;
		bool isParallel(const Vector&) const;
		bool normalize();
		/**
		*\brief Longitud del vector
		*/		
		OCTETOS_MATH_DECIMAL length()const;
		bool isOrthogonal(const Vector&) const;
		/**
		*\brief Proyeccion de a(this) en la direccion de b
		*/
		Vector Proj(const Vector& b);
		/**
		*\brief Component de a(this) en la direccion de b
		*/		
		OCTETOS_MATH_DECIMAL Comp(const Vector& b);
		//bool isNull()const;
		bool isLinIndep(const Vector&)const;
		bool isLinDep(const Vector&)const;		
		/**
		*\brief Expresa el vector actual como un combinacion lineal de los vectores a y b
		*/		
		bool combLineal(const Vector& a, const Vector& b, OCTETOS_MATH_DECIMAL& s, OCTETOS_MATH_DECIMAL& t);

		OCTETOS_MATH_DECIMAL slope()const;
		
		bool translate(const Vector& a);
		bool rotate(const Vector& a);
		bool reflect(const Vector& a);
		/**
		*\brief rota(radianes) el punto this alrededor de origen
		*/
		bool rotate(OCTETOS_MATH_DECIMAL theta);
		/**
		*\brief cos del angulo(radian) formado por el vectora actual y el prametro b
		*/
		OCTETOS_MATH_DECIMAL cos(const Vector& b)const;
		/**
		*\brief sen del angulo(radian) formado por el vectora actual y el prametro b
		*/
		OCTETOS_MATH_DECIMAL sen(const Vector& b)const;
		/**
		*\brief tan del angulo(radian) formado por el vectora actual y el prametro b
		*/
		OCTETOS_MATH_DECIMAL tan(const Vector& b)const;
		
	protected:
		
	private:
	};

	//static const Vector NullVector(O);

	class Line
	{
	public:
		//constructor
		Line();
		Line(const Vector& p0,const Vector& p1);
		Line(OCTETOS_MATH_DECIMAL b, OCTETOS_MATH_DECIMAL m);

		//operator
		operator std::string() const;
		
		//

		//
		bool isParallel(const Vector&) const;
		bool isOrthogonal(const Vector&) const;
		bool isParallel(const Line&) const;
		OCTETOS_MATH_DECIMAL distance(const Vector&) const;
		OCTETOS_MATH_DECIMAL onX(OCTETOS_MATH_COORDENATE x)const;
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_DECIMAL onXY(OCTETOS_MATH_COORDENATE x,OCTETOS_MATH_COORDENATE y)const;
#endif
		Line orthogonalOn(const Vector&)const;
	private:
		Vector p0;
		Vector a;
		OCTETOS_MATH_DECIMAL m;
	};
	
	class Circumference
	{
	public:
		Circumference(OCTETOS_MATH_DECIMAL r);	
		/**
		*\brief returna el valor absoluto de 
		*/		
		OCTETOS_MATH_DECIMAL onX(OCTETOS_MATH_COORDENATE x)const;
	private:
		OCTETOS_MATH_DECIMAL radio2;
	};
	
	class Parable
	{
	public:
		Parable(OCTETOS_MATH_DECIMAL p);
		/**
		*\brief returna el valor absoluto de 
		**/		
		OCTETOS_MATH_DECIMAL onX(OCTETOS_MATH_COORDENATE x)const;
		
	private:
		OCTETOS_MATH_DECIMAL p4;
	};
	
	class Ellipse
	{
	public:
		Ellipse(OCTETOS_MATH_DECIMAL a,OCTETOS_MATH_DECIMAL b);
		/**
		*\brief returna el valor absoluto de 
		*/		
		OCTETOS_MATH_DECIMAL onX(OCTETOS_MATH_COORDENATE x)const;
		
	private:
		OCTETOS_MATH_DECIMAL a2,b2;
	
	};
		
	class Hyperbola
	{
	public:
		Hyperbola(OCTETOS_MATH_DECIMAL a,OCTETOS_MATH_DECIMAL b);
		/**
		*\brief returna el valor absoluto de 
		*/		
		OCTETOS_MATH_DECIMAL onX(OCTETOS_MATH_COORDENATE x)const;
		
	private:
		OCTETOS_MATH_DECIMAL a2,b2;
	
	};
}
} 


#endif 
