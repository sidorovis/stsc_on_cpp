#ifndef _STSC_DATAFEED_BINARY_READER_H_
#define _STSC_DATAFEED_BINARY_READER_H_

#include <istream>

#include <binary_format.h>

namespace stsc
{
	namespace datafeed
	{
		std::istream& operator>>( std::istream& out, binary_period& bp );
	}
}

#endif // _STSC_DATAFEED_BINARY_READER_H_