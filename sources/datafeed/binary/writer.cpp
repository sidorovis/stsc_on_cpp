#include <binary/writer.h>

namespace stsc
{
	namespace datafeed
	{
		namespace binary
		{
			std::ostream& operator<<( std::ostream& out, const period& bp )
			{
				typedef const char* const outtype;

				static const size_t header_size = sizeof( bp.header );
				static const size_t bar_size = sizeof( common::price_bar );

				out.write( reinterpret_cast< outtype >( &bp.header ), sizeof( bp.header ) );
				out.write( reinterpret_cast< outtype >( &(bp.bars[0]) ), sizeof( common::price_bar ) * bp.bars.size() );
				return out;
			}
		}
	}
}
