#include <common/types.h>

namespace stsc
{
	namespace common
	{
		shared_string make_shared_string( const std::string& str )
		{
			return shared_string( new std::string( str ) );
		}
	}
}
