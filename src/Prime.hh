
#ifndef OCTETOS_PRIME_HH
#define OCTETOS_PRIME_HH

#include <vector>
#include <string>
#include <iostream>

namespace math
{

class Prime
{
public:
	Prime();
	/*
	*
	*/
	bool isPrime(long n);
	bool isDiv3(long n);
	bool isDiv5(long n);
private:
	std::vector<long> knows;

	//
	
};

}

#endif
