
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
}
