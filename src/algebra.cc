
#include "algebra.hh"

namespace algebra
{

	Literal::Literal(wchar_t l)
	{
		literal = l;
		numerator = 1;
		denominator = 1;
	}
	Literal::Literal(wchar_t l, int n, int d)
	{
		literal = l;
		numerator = n;
		denominator = d;
	}
	wchar_t Literal::getValue()const
	{
		return literal;
	}


	Quadratic::Quadratic(double A,double B,double C,double D,double E,double F)
	{
		this->A = A;
		this->B = B;
		this->C = C;
		this->D = D;
		this->E = E;
		this->F = F;
	}

	
}
