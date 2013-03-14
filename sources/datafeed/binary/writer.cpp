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
				out.write( reinterpret_cast< outtype >( &bp.header ), sizeof( bp.header ) );
				out.write( reinterpret_cast< outtype >( &(bp.bars[0]) ), sizeof( common::price_bar ) * bp.bars.size() );
				return out;
			}
		}
	}
}
