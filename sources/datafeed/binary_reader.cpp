#include <binary_reader.h>

namespace stsc
{
	namespace datafeed
	{
		std::istream& operator>>( std::istream& in, binary_period& bp )
		{
			typedef char* intype;
			in.read( reinterpret_cast< intype >( &bp.header ), sizeof( bp.header ) );
			bp.bars.resize( bp.header.elements_size );
			in.read( reinterpret_cast< intype >( &(bp.bars[0]) ), sizeof( common::price_bar ) * bp.header.elements_size );
			return in;
		}
	}
}
