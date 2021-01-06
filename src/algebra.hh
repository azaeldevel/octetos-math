
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


	
	
	
} 


#endif