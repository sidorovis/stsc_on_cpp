#ifndef _STSC_DATAFEED_BINARY_READER_H_
#define _STSC_DATAFEED_BINARY_READER_H_

#include <istream>

#include <binary/format.h>

namespace stsc
{
	namespace datafeed
	{
		namespace binary
		{
			std::istream& operator>>( std::istream& in, period& bp );
			std::istream& read_part( std::istream& in, period& bp, const long from, const long to );
		}
	}
}

#endif // _STSC_DATAFEED_BINARY_READER_H_