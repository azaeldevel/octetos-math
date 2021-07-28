

#ifndef OCTETOS_MATH_MATRIX_HH
#define OCTETOS_MATH_MATRIX_HH

#include <vector>
#include <octetos/core/Exception.hh>



#include "core.hh"

namespace oct::math
{

template<class T> class Matrix;

template<class T>
struct Row : private std::vector<T>
{
	friend Matrix<T>;

	T& operator [](unsigned short i)
	{
		return std::vector<T>::operator[](i);
	}

private:
	void resize(unsigned short l)
	{
		std::vector<T>::resize(l);
	}
};



template<class T>
class Matrix : private std::vector<Row<T>>
{
public:
	Matrix()
	{
	}

	Matrix(unsigned short lines,unsigned short columns)
	{
		std::vector<Row<T>>::resize(lines);
		for(std::vector<T>& v : *this)
		{
			v.resize(columns);
		}
	}

	Matrix(unsigned short number)
	{
		std::vector<Row<T>>::resize(number);
		for(std::vector<T>& v : *this)
		{
			v.resize(number);
		}
	}

	Matrix<T> operator +(const Matrix<T>& o)
	{
		if(columns() != o.columns()) throw octetos::core::Exception("Dimensiones de las amtrices no compatibles",__FILE__,__LINE__);
		if(rows() != o.rows()) throw octetos::core::Exception("Dimensiones de las amtrices no compatibles",__FILE__,__LINE__);

		Matrix<T> mat(rows(),columns());
		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < Matrix<T>::at(i).size() ; j++)
			{
				mat[i][j] = Matrix<T>::at(i).at(j) + o.at(i).at(j);
			}
		}

		return mat;
	}
	Matrix<T> operator -(const Matrix<T>& o)
	{
		if(columns() != o.columns()) throw octetos::core::Exception("Dimensiones de las amtrices no compatibles",__FILE__,__LINE__);
		if(rows() != o.rows()) throw octetos::core::Exception("Dimensiones de las amtrices no compatibles",__FILE__,__LINE__);

		Matrix<T> mat(rows(),columns());
		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < Matrix<T>::at(i).size() ; j++)
			{
				mat[i][j] = Matrix<T>::at(i).at(j) - o.at(i).at(j);
			}
		}

		return mat;
	}
	Matrix<T> operator * (const Matrix<T>& o)
	{
		if(columns() != o.rows()) throw octetos::core::Exception("Dimensiones de las matrices no compatibles",__FILE__,__LINE__);
		
		Matrix<T> mat(rows(),o.columns());
		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < o.at(i).size() ; j++)
			{
				for(unsigned short k = 0; k < Matrix<T>::at(i).size() ; k++)
				{
					mat[i][j] += Matrix<T>::at(i).at(k) * o.at(k).at(j);
				}
			}
		}

		return mat;
	}
	bool operator == (const Matrix<T>& o)
	{
		if(columns() != o.columns()) throw octetos::core::Exception("Dimensiones de las matrices no compatibles",__FILE__,__LINE__);
		if(rows() != o.rows()) throw octetos::core::Exception("Dimensiones de las matrices no compatibles",__FILE__,__LINE__);
		
		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < o.at(i).size() ; j++)
			{
				if(Matrix<T>::at(i).at(j) != o.at(i).at(j)) return false;
			}
		}

		return true;
	}

	std::vector<T>& operator [](unsigned short i)
	{
		return std::vector<Row<T>>::operator[](i);
	}

	void transposed(Matrix<T>& m)const
	{
		if(Matrix<T>::at(0).size() != m.size())
		{
			m.resize(Matrix<T>::at(0).size());
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

	bool isSquared()const
	{
		unsigned short n = Matrix<T>::size();
		
		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < Matrix<T>::at(i).size() ; j++)
			{
				if( Matrix<T>::at(i).size() != n ) return false;
			}
		}

		return true;
	}

	bool isDiagonal() const
	{
		if(not isSquared()) return false;
		for(unsigned short i = 0; i < Matrix<T>::size() ; i++)
		{
			for(unsigned short j = 0; j < Matrix<T>::at(i).size() ; j++)
			{
				if(i != j)
				{
					if(Matrix<T>::at(i).at(j) != 0)
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	unsigned short rows() const
	{
		return std::vector<Row<T>>::size();
	}
	unsigned short columns() const
	{
		if(std::vector<Row<T>>::size() == 0) return 0;
		return std::vector<Row<T>>::at(0).size();
	}
	
};



}

#endif