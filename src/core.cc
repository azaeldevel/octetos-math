
#include <core.hh>


namespace math
{
	Exception::Exception(const std::string& msg,const char* fn,int line) : octetos::core::Exception(msg,fn,line)
	{}
	Exception::Exception(const std::string& msg): octetos::core::Exception(msg)
	{}



	/*template<> bool Measure<double>::operator == (const Measure<double>& obj)const
	{
		if(fabs(u - obj.u) < epsilon)
		{
			throw Exception("Los tipos de unidades no coincide.");
		}
		if(fabs(v - obj.v) < epsilon) return true;
		return false;
	}
	template<> bool Measure<float>::operator == (const Measure<float>& obj)const
	{
		if(fabs(u - obj.u) < epsilon)
		{
			throw Exception("Los tipos de unidades no coincide.");
		}
		if(fabs(v - obj.v) < epsilon) return true;
		return false;
	}

	
	template<> bool Measure<double>::operator == (double value)const
	{
		if(fabs(v - value) < epsilon) return true;
		return false;
	}
	template<> bool Measure<float>::operator == (float value)const
	{
		if(fabs(v - value) < epsilon) return true;
		return false;
	}*/


}
