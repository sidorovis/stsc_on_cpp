#ifndef _STSC_DATAFEED_BINARY_FORMAT_H_
#define _STSC_DATAFEED_BINARY_FORMAT_H_

#include <vector>

#include <boost/cstdint.hpp>

#include <common/bar_types.h>

namespace stsc
{
	namespace datafeed
	{
		namespace binary
		{
			struct period_header
			{
				boost::uint32_t finished;
				boost::uint32_t version;
				boost::uint32_t elements_size;
			};

			struct period
			{
				period_header header;
				typedef std::vector< common::price_bar > bars_type;
				bars_type bars;
			};
		}
	}
}

#endif // _STSC_DATAFEED_BINARY_FORMAT_H_