#include "moving_median_indicator.h"

#include <math.h>
#include <strategies_engine.h>

namespace stsc
{
	namespace engine
	{
		moving_median_indicator::moving_median_indicator( const std::string& name,
														strategies_engine& se, 
														const std::string& moving_median_subscription_name,
														const common::bar_data::float_type bigger_than,
														const common::bar_data::float_type less_than )
			: base_type( name, se )
			, moving_median_series_( se.subscribe< common::bar_data::float_type >( moving_median_subscription_name ) )
			, bigger_than_( bigger_than )
			, less_than_( less_than )
			
		{
			if ( bigger_than_ >= less_than_ )
				throw std::invalid_argument( "moving_median_indicator: bigger_than value is bigger than less_than value" );
		}
		moving_median_indicator::~moving_median_indicator()
		{
		}
		void moving_median_indicator::process( const bar_type& b )
		{
			const common::bar_data::float_type* price = moving_median_series_.at( &b );
			if ( price )
			{
				const common::bar_data::float_type diff = b.close_ - *price;
				if ( fabs( diff ) > bigger_than_  && fabs( diff ) < less_than_ )
				{
					const common::open_signal::side side = diff < 0 ? common::open_signal::side_long : common::open_signal::side_short;
					registrate_signal( b, new common::open_signal( side ) );
				}
			}
		}
	}
}
