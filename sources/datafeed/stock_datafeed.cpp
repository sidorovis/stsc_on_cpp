#include <stock_datafeed.h>

namespace stsc
{
	namespace datafeed
	{
		stock_datafeed::stock_datafeed( const common::shared_string& sn )
			: stock_name( sn )
		{

		}
		void stock_datafeed::set_datafeed( datafeed_period& dp )
		{
			datafeed = dp;
			index = 0;
			ci = datafeed.get()->bars.begin();
		}
		//
		const bool stock_datafeed::finished() const
		{
			return ci == datafeed.get()->bars.end();
		}
		const long stock_datafeed::current_day() const
		{
			if ( finished() )
				throw std::logic_error( "stock datafeed '" + *stock_name + "' processed" );
			return ci->time_;
		}
		//
		void stock_datafeed::increment() 
		{
			++index;
			++ci;
		}
		//
		common::on_stock_bar stock_datafeed::create_on_stock_bar() const
		{
			return common::on_stock_bar( *ci, index );
		}
		common::on_bar stock_datafeed::create_on_bar() const
		{
			return common::on_bar( *ci, index );
		}
		common::on_period stock_datafeed::create_on_period() const
		{
			return common::on_period( *ci, index );
		}
	}
}
