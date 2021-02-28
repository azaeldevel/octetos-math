
#include <core.hh>


namespace math
{
	Exception::Exception(const std::string& msg,const char* fn,int line) : octetos::core::Exception(msg,fn,line)
	{}
	Exception::Exception(const std::string& msg): octetos::core::Exception(msg)
	{}
}
