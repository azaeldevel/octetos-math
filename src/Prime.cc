
#include "Prime.hh"

namespace math
{
	
Prime::Prime()
{
	knows.push_back(2);
	knows.push_back(3);
	knows.push_back(5);
	knows.push_back(7);
}

bool Prime::isPrime(long n)
{
	//por definicion
	if(n == 0) return false;
	if(n == 1) return false;

	//verificar en la lista conocida
	for(long i : knows)
	{
		if(i == n) return true;
	}

	long newnumber = 0;
	//si es divisible por algono de la lista
	for(long i = 0; i < knows.size(); i++)
	{
		if(n % knows.at(i) == 0) 
		{
			return false;
		}
		newnumber = i;
	}		
	knows.push_back(newnumber);

	for(long i = 0; i < knows.size(); i++)
	{
		if(n % knows.at(i) == 0) 
		{
			return false;
		}
		newnumber = i;
	}		
	knows.push_back(newnumber);
	
	return true;
}

bool Prime::isDiv3(long n)
{
	std::string strn = std::to_string(n);
	int sums = 0;

	for(int i = 0; i < strn.size(); i++)
	{
		char cd = strn.at(i);
		//std::cout << cd << ",";
		sums += cd - 48;
	}
	//std::cout << "sum = " <<sums << "\n";;

	if(sums % 3 == 0) return true;
	return false;
}

bool Prime::isDiv5(long n)
{
	std::string strn = std::to_string(n);

	char cd = strn.at(strn.size() - 1);
	int val = cd - 48;


	if(val == 0 or val == 5) return true;
	return false;
}

}