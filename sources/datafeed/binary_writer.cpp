#include <binary_writer.h>

namespace stsc
{
	namespace datafeed
	{
		std::ostream& operator<<( std::ostream& out, const binary_period& bp )
		{
			typedef const char* const outtype;
			out.write( reinterpret_cast< outtype >( &bp.header ), sizeof( bp.header ) );
			out.write( reinterpret_cast< outtype >( &(bp.bars[0]) ), sizeof( common::price_bar ) * bp.bars.size() );
			return out;
		}
	}
}
