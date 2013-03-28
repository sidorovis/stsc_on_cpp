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

				static const size_t header_size = sizeof( bp.header );
				static const size_t bar_size = sizeof( common::price_bar );

				in.read( reinterpret_cast< intype >( &bp.header ), header_size );
				bp.bars.resize( bp.header.elements_size );
				in.read( reinterpret_cast< intype >( &(bp.bars[0]) ), bar_size * bp.header.elements_size );
				return in;
			}
		}
	}
}
