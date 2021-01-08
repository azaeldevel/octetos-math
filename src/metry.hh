
#ifndef OCTETOS_MATH_GEOMETRY_HH
#define OCTETOS_MATH_GEOMETRY_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>

//#define OCTETOS_MATH_BASEPOINT double
#define OCTETOS_MATH_COORDENATE double
#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_EPSILON 0.0001
#define OCTETOS_MATH_DIMENSION 2
//#define DEBUG

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
#if OCTETOS_MATH_DIMENSION == 2
		Point(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y);
#elif OCTETOS_MATH_DIMENSION == 3
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
#endif
	
	class Vector : public Point
	{
	public:
		//contructor
		Vector();
		Vector(const Point& end);
		Vector(const Vector&);
#if OCTETOS_MATH_DIMENSION == 2
		Vector(OCTETOS_MATH_COORDENATE x, OCTETOS_MATH_COORDENATE y);
#elif OCTETOS_MATH_DIMENSION == 3
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
		bool isNull()const;
		bool isLinIndep(const Vector&)const;
		bool isLinDep(const Vector&)const;		
		/**
		*\brief Expresa el vector actual como un combinacion lineal de los vectores a y b
		*/		
		bool combLinIndep(const Vector& a, const Vector& b, OCTETOS_MATH_DECIMAL& s, OCTETOS_MATH_DECIMAL& t);
#if OCTETOS_MATH_DIMENSION == 2
		OCTETOS_MATH_DECIMAL slope()const;
#elif OCTETOS_MATH_DIMENSION == 3
		OCTETOS_MATH_DECIMAL slope()const;
		OCTETOS_MATH_DECIMAL slopeY()const;
#endif
		
	protected:
		
	private:
	};

	static const Vector NullVector(O);

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
		bool isParallel(const Point&) const;
		bool isOrthogonal(const Point&) const;
		bool isParallel(const Line&) const;
		OCTETOS_MATH_DECIMAL distance(const Vector&) const;
		OCTETOS_MATH_DECIMAL onX(OCTETOS_MATH_COORDENATE x)const;
#if OCTETOS_MATH_DIMENSION == 3
		OCTETOS_MATH_DECIMAL onXY(OCTETOS_MATH_COORDENATE x,OCTETOS_MATH_COORDENATE y)const;
#endif
		Line orthogonalOn(const Vector&)const;
	private:
		Vector p0;
		Vector a;
		OCTETOS_MATH_DECIMAL m;
	};

	
	
}
} 


#endif 
