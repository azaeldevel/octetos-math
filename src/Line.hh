
#ifndef OCTETOS_MATH_LINE_HH
#define OCTETOS_MATH_LINE_HH

#include <Vector.hh>


namespace metry::rect
{
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


#endif
