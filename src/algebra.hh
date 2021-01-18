
#ifndef OCTETOS_MATH_ALGEBRA_HH
#define OCTETOS_MATH_ALGEBRA_HH


namespace algebra
{

	class Literal
	{
	public:
		Literal(wchar_t literal);
		Literal(wchar_t literal, int numerator, int denominator);
		wchar_t getValue() const;

	protected:
		
	private:
		wchar_t literal;
		int numerator;
		int denominator;
	};


	class Equation
	{
	
	public:
	};
	
	class Quadratic : public Equation
	{
	
	public:
		Quadratic(double A,double B,double C,double D,double E,double F);

	private:
		double A,B,C,D,E,F,x,y;
		
	};
	
} 


#endif