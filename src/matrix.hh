

#ifndef OCTETOS_MATH_MATRIX_HH
#define OCTETOS_MATH_MATRIX_HH

#include <vector>
#include <octetos/core/Exception.hh>



#include "core.hh"

namespace oct::math
{

template<class T>
class Matrix : public std::vector<std::vector<T>>
{
public:
	Matrix()
	{

	}
	Matrix(unsigned short lines,unsigned short columns)
	{
		std::vector<std::vector<T>>::resize(lines);
		for(std::vector<T>& v : *this)
		{
			v.resize(columns);
		}
	}
	Matrix(unsigned short number)
	{
		std::vector<std::vector<T>>::resize(number);
		for(std::vector<T>& v : *this)
		{
			v.resize(number);
		}
	}

	void transposed(Matrix<T>& m)const
	{
		if(Matrix<T>::at(0).size() != m.size())
		{
			m.resize(Matrix<T>::at(0).size());
			std::cout << "Matrix<T>::at(0).size() = " << Matrix<T>::at(0).size() << "\n";
			for(unsigned short i = 0; i < m.size() ; i++)
			{
				m[i].resize(Matrix<T>::size());
			}
		}		

		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < Matrix<T>::at(i).size() ; j++)
			{
				m[j][i] = Matrix<T>::at(i).at(j);
			}
		}
	}

	void print(std::ostream& out) const
	{
		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < Matrix<T>::at(i).size() ; j++)
			{
				out << Matrix<T>::at(i).at(j);
				out << ",";
			}
			out << "\n";
		}
	}
};

}

#endif