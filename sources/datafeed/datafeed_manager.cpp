#include <datafeed_manager.h>

namespace stsc
{
	namespace datafeed
	{
		namespace details
		{
			on_stock_bar::on_stock_bar( const shared_string& sn, const common::price_bar& b, const size_t i )
				: stock_name( sn )
				, value( b )
				, index( i )
			{
			}
			on_bar::on_bar( const common::bar_type& b, const size_t i )
				: value( b )
				, index( i )
			{
			}
			on_period::on_period( const common::bar_type& b, const size_t i )
				: value( b )
				, index( i )
			{
			}
			on_period::on_period()
			{
			}
			//
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
			on_stock_bar stock_data::create_on_stock_bar() const
			{
				return on_stock_bar( stock_name, *ci, index );
			}
			on_bar stock_data::create_on_bar() const
			{
				return on_bar( *ci, index );
			}
			on_period stock_data::create_on_period() const
			{
				return on_period( *ci, index );
			}
		}
		datafeed_manager::datafeed_manager()
		{
		}
		datafeed_manager::~datafeed_manager()
		{
		}
		//
		void datafeed_manager::new_bar_on_stock( const details::on_stock_bar& bar )
		{
		}
		void datafeed_manager::new_bar_on_bar( const details::on_bar& bar )
		{
		}
		void datafeed_manager::new_bar_on_period( const details::on_period& bar )
		{
		}
		void datafeed_manager::file_reading_error( const std::string& file_path )
		{
		}
	}
}
