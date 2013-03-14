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
			std::istream& operator>>( std::istream& out, period& bp );
		}
	}
}

#endif // _STSC_DATAFEED_BINARY_READER_H_