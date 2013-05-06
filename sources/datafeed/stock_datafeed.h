#ifndef _STSC_DATAFEED_STOCK_DATAFEED_H_
#define _STSC_DATAFEED_STOCK_DATAFEED_H_

#include <boost/shared_ptr.hpp>

#include <common/types.h>

#include <binary/format.h>

namespace stsc
{
	namespace datafeed
	{
		class stock_datafeed
		{
		public:
			typedef boost::shared_ptr< binary::period > datafeed_period;

			const common::shared_string stock_name;
		private:
			datafeed_period datafeed;
			binary::period::bars_type::const_iterator ci;
			size_t index;
			//
		public:
			explicit stock_datafeed( const common::shared_string& stock_name );
			//
			void set_datafeed( datafeed_period& dp );
			//
			const bool finished() const;
			const long current_day() const;
			//
			void increment();
			//
			common::on_stock_bar create_on_stock_bar() const;
			common::on_bar create_on_bar() const;
			common::on_period create_on_period() const;
		};
		typedef boost::shared_ptr< stock_datafeed > stock_datafeed_ptr;
	}
}

#endif // _STSC_DATAFEED_STOCK_DATAFEED_H_

