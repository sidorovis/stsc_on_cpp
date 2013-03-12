#include <binary/reader.h>

namespace stsc
{
	namespace datafeed
	{
		namespace binary
		{
			std::istream& operator>>( std::istream& in, period& bp )
			{
				typedef char* intype;
				in.read( reinterpret_cast< intype >( &bp.header ), sizeof( bp.header ) );
				bp.bars.resize( bp.header.elements_size );
				in.read( reinterpret_cast< intype >( &(bp.bars[0]) ), sizeof( common::price_bar ) * bp.header.elements_size );
				return in;
			}
		}
	}
}
