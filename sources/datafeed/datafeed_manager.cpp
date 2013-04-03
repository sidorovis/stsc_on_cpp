#include <datafeed_manager.h>

namespace stsc
{
	namespace datafeed
	{
		namespace details
		{
			stock_data::stock_data( const shared_string& sn )
				: stock_name( sn )
			{

			}
			void stock_data::set_datafeed( datafeed_period& dp )
			{
				datafeed = dp;
				ci = datafeed.get()->bars.begin();
			}
			const bool stock_data::finished() const
			{
				return ci == datafeed.get()->bars.end();
			}
			const long stock_data::current_day() const
			{
				if ( finished() )
					throw std::logic_error( "stock datafeed '" + *stock_name + "' processed" );
				return ci->time_;
			}
		}
		datafeed_manager::datafeed_manager()
		{
		}
		datafeed_manager::~datafeed_manager()
		{
		}
		//
		void datafeed_manager::new_bar_on_stock( const shared_string& stock_name, const common::price_bar& bar )
		{
		}
		void datafeed_manager::new_bar_on_bar( const common::bar_type& bar )
		{
		}
		void datafeed_manager::new_bar_on_period( const common::bar_type& bar )
		{
		}
		void datafeed_manager::file_reading_error( const std::string& file_path )
		{
		}
	}
}
