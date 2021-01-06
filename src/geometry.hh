
#ifndef OCTETOS_MATH_GEOMETRY_HH
#define OCTETOS_MATH_GEOMETRY_HH

#include <vector>
#include <list>
#include <string>
#include <octetos/core/Exception.hh>


#define OCTETOS_MATH_BASEPOINT double
#define OCTETOS_MATH_DECIMAL double
#define OCTETOS_MATH_EPSILON 0.0001
#define OCTETOS_MATH_UNIT 100

namespace geometry
{
	namespace core
	{
		//static char RECTANGULAR = 'R';
		//static char CIRCULAR = 'C';
		 
		class Point : public std::vector<OCTETOS_MATH_BASEPOINT>
		{
		public:
			//contructor
			Point(const Point& obj);
			Point(int dimension,char type);

			//getter
			char getType()const;
			const char* getTypeDescribe()const;

			//operators
			const Point& operator= (const Point&);
		private:
			int dimension;
			/**
			* R:Rectangular, C:Circular
			*/
			char type;
		};
		class Plane : protected std::list<Point*>
		{
		public:
			//contructor
			Plane(int dimension,char type);

			//getter
			char getType()const;
			const char* getTypeDescribe()const;

			//funtions
			
		private:
			int dimension;
			/**
			* R:Rectangular, C:Circular
			*/
			char type;	
		};
		
	}


	
	namespace D2
	{
		class Point : public core::Point
		{
		public:
			//contructor
			Point();
			Point(const Point& obj);
			Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y);

			//operators
			operator std::string() const;


			//getter
			OCTETOS_MATH_BASEPOINT getX() const;
			OCTETOS_MATH_BASEPOINT getY() const;

			//funtions
			virtual OCTETOS_MATH_DECIMAL distance(const Point& p0)const;
			virtual bool rotate(const Point& eje);
			virtual bool normalize();

		protected:
			Point(int dimension,char type);
		};
		
		static const Point O(0.0,0.0);

		class Plane : public core::Plane
		{
		public:
			//contructor
			Plane();
			
			//funtions
			
		protected:
			Plane(int dimension,char type);
		};
		
		class Vector
		{
		public:
			//contructor
			Vector();
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
		protected:

		private:
			Point begin;
			Point end;
		};
	}
	
	
	namespace D3
	{
		class Point : public D2::Point
		{

		public:
			//contructor
			Point();
			Point(OCTETOS_MATH_BASEPOINT x, OCTETOS_MATH_BASEPOINT y,OCTETOS_MATH_BASEPOINT z);
			
			//getter
			OCTETOS_MATH_BASEPOINT getZ() const;

		protected:
			Point(int dimension,char type);
		};

		static Point O(0,0,0);

		class Plane : public D2::Plane
		{
		public:
			//contructor
			Plane();
			
			//funtions
			static OCTETOS_MATH_DECIMAL distance(const Point& p0,const Point& p1);
			
		protected:
			Plane(int dimension,char type);
		};
	} 
 


	
} 


#endif 
