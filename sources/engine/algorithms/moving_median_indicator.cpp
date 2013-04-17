#include <algorithms/moving_median_indicator.h>

#include <math.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms
		{
			moving_median_indicator::moving_median_indicator( const std::string& name,
															const float_type bigger_than,
															const float_type less_than )
				: base_type( name )
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
				//const common::bar_data::float_type* price = moving_median_series_.ptr_at( &b );
				//if ( price )
				//{
				//	const common::bar_data::float_type diff = b.close_ - *price;
				//	if ( fabs( diff ) > bigger_than_  && fabs( diff ) < less_than_ )
				//	{
				//		const common::open_signal::side side = diff < 0 ? common::open_signal::side_long : common::open_signal::side_short;
				//		registrate_signal( b, new common::open_signal( side ) );
				//	}
				//}
			}
		}
	}
}
