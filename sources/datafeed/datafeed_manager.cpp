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
				index = 0;
				ci = datafeed.get()->bars.begin();
			}
			//
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
			//
			void stock_data::increment() 
			{
				++index;
				++ci;
			}
			//
			common::on_stock_bar stock_data::create_on_stock_bar() const
			{
				return common::on_stock_bar( *ci, index );
			}
			common::on_bar stock_data::create_on_bar() const
			{
				return common::on_bar( *ci, index );
			}
			common::on_period stock_data::create_on_period() const
			{
				return common::on_period( *ci, index );
			}
		}
		datafeed_manager::datafeed_manager()
		{
		}
		datafeed_manager::~datafeed_manager()
		{
		}
		//
		void datafeed_manager::new_bar_on_stock( const common::on_stock_bar& bar )
		{
		}
		void datafeed_manager::new_bar_on_bar( const common::on_bar& bar )
		{
		}
		void datafeed_manager::new_bar_on_period( const common::on_period& bar )
		{
		}
		//
		void datafeed_manager::file_reading_error( const std::string& file_path )
		{
		}
	}
}
