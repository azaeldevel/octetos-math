
#ifndef OCTETOS_MATH_GEOMETRY_HH
#define OCTETOS_MATH_GEOMETRY_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>

//#define OCTETOS_MATH_BASEPOINT double
#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_EPSILON 0.0001
#define OCTETOS_MATH_DIMENSION 2

namespace metry
{

	class Point : public std::vector<OCTETOS_MATH_DECIMAL>
	{
	public:
		//contructor
		Point();
		Point(const Point& obj);
#if OCTETOS_MATH_DIMENSION == 2
		Point(OCTETOS_MATH_DECIMAL x, OCTETOS_MATH_DECIMAL y);
#elif OCTETOS_MATH_DIMENSION == 3
		Point(OCTETOS_MATH_DECIMAL x, OCTETOS_MATH_DECIMAL y, OCTETOS_MATH_DECIMAL z);
#endif
		
		//getter
		OCTETOS_MATH_DECIMAL getX() const;
		OCTETOS_MATH_DECIMAL getY() const;
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_DECIMAL getZ() const;
#endif
		char getType()const;
		const char* getTypeDescribe()const;
		
		//operators
		operator std::string() const;
		const Point& operator= (const Point&);
		bool operator ==(const Point&);

		//funtion
		OCTETOS_MATH_DECIMAL distance(const Point& p)const;
		
	private:
		int dimension;
		/**
		* R:Rectangular, C:Circular
		*/
		char type;
	};
	
namespace vector
{
#if OCTETOS_MATH_DIMENSION == 2
	static const Point O(0.0,0.0);
#elif OCTETOS_MATH_DIMENSION == 3
	static const Point O(0.0,0.0,0.0);
#endif
	
	class Vector
	{
	public:
		//contructor
		Vector();
		Vector(const Vector&);
		Vector(const Point& end);
		Vector(const Point& begin,const Point& end);
			
		//getter
		const Point& getBegin()const;
		const Point& getEnd()const;
			
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
		
	protected:
		
	private:
		Point begin;
		Point end;
	};

	static const NullVector(O,O);

	class Line
	{	
	public:
		//constructor
		Line(const Point& p0,const Point& a);
		Line(OCTETOS_MATH_DECIMAL b, OCTETOS_MATH_DECIMAL m);
		Line(const Vector&);
		
		//
		Point getPoint(OCTETOS_MATH_DECIMAL t)const;
		Vector getVector(OCTETOS_MATH_DECIMAL t)const;

		//
		bool isParallel(const Point&) const;
		bool isOrthogonal(const Point&) const;
		bool isParallel(const Line&) const;
		Vector orthogonalIn(const Point&) const;
		
	private:
		Vector vector;
	};
	
}
} 


#endif 
