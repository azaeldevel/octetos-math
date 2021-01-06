
#ifndef OCTETOS_MATH_GEOMETRY_HH
#define OCTETOS_MATH_GEOMETRY_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>

#define OCTETOS_MATH_BASEPOINT double
#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_EPSILON 0.0001
#define OCTETOS_MATH_DIMENSION 2

namespace metry
{

	class Point : public std::vector<OCTETOS_MATH_BASEPOINT>
	{
	public:
		//contructor
		Point();
		Point(const Point& obj);
		Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y);
#if OCTETOS_MATH_DIMENSION >= 3
		Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y,OCTETOS_MATH_BASEPOINT z);
#endif
		
		//getter
		OCTETOS_MATH_BASEPOINT getX() const;
		OCTETOS_MATH_BASEPOINT getY() const;
#if OCTETOS_MATH_DIMENSION >= 3
		OCTETOS_MATH_BASEPOINT getZ() const;
#endif
		char getType()const;
		const char* getTypeDescribe()const;
		
		//operators
		operator std::string() const;
		const Point& operator= (const Point&);
		bool operator ==(const Point&);

		//funtion
		OCTETOS_MATH_DECIMAL distance(const Point& p0)const;
		
	private:
		int dimension;
		/**
		* R:Rectangular, C:Circular
		*/
		char type;
	};
	
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
		OCTETOS_MATH_DECIMAL operator*(const Vector&);
		Vector operator+(const Vector&);
		Vector operator-(const Vector&);
		Vector operator*(OCTETOS_MATH_DECIMAL);
		Vector operator/(OCTETOS_MATH_DECIMAL);
		const Vector& operator= (const Vector&);

		//funtions
		Vector orthogonal() const;
		bool isParallel(const Vector&) const;
	protected:

	private:
		Point begin;
		Point end;
	};

	
	
 


	
} 


#endif 
