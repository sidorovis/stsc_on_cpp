#ifndef _STSC_DATAFEED_BINARY_WRITER_H_
#define _STSC_DATAFEED_BINARY_WRITER_H_

#include <ostream>

#include <binary/format.h>

namespace stsc
{
	namespace datafeed
	{
		namespace binary
		{
			std::ostream& operator<<( std::ostream& out, const period& bp );
		}
	}
}

#endif // _STSC_DATAFEED_BINARY_WRITER_H_