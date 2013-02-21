#ifndef _STSC_DATAFEED_BINARY_WRITER_H_
#define _STSC_DATAFEED_BINARY_WRITER_H_

#include <ostream>

#include <binary_format.h>

namespace stsc
{
	namespace datafeed
	{
		std::ostream& operator<<( std::ostream& out, const binary_period& bp );
	}
}

#endif // _STSC_DATAFEED_BINARY_WRITER_H_