
#ifndef OCTETOS_MATH_ALGEBRA_HH
#define OCTETOS_MATH_ALGEBRA_HH


namespace oct::math
{
	template<class T>
	class Equation
	{
	
	public:
		virtual void solve() = 0;
	};
	
	template<class T>
	class Quadratic : public Equation<T>
	{
	public:
		Quadratic(T A,T B,T C,T D,T E,T F);
		{
			this->A = A;
			this->B = B;
			this->C = C;
			this->D = D;
			this->E = E;
			this->F = F;
		}
		Quadratic(T A,T B,T C);
		{
			this->A = A;
			this->B = B;
			this->C = C;
			this->D = 0;
			this->E = 0;
			this->F = 0;
		}

		virtual void solve()
		{
			//Ref : [1], pag 252, 9.11
			T B2 = pow(B,2);
			T v1 = pow(A+C,2);
			T v2 = v1 + 4 * (B2 - (A*C));
			T v3 = sqrt(v2);

			x = ((A+C) - v3) / 2;
			y = ((A+C) + v3) / 2;
		}
		
	private:
		T A,B,C,D,E,F,x,y;
		
	};
	
} 


#endif