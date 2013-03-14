#include "moving_median_indicator.h"

#include <math.h>
#include <strategies_engine.h>

namespace stsc
{
	namespace engine
	{
		moving_median_indicator::moving_median_indicator( const std::string& name,
														strategies_engine& se, 
														const size_t moving_median_window,
														const common::bar_data::float_type bigger_than,
														const common::bar_data::float_type less_than,
														const common::bar_data_types::value type )
			: base_type( name, se )
			, data_type_in_use_( type )
			, bigger_than_( bigger_than )
			, less_than_( less_than )
		{
			if ( bigger_than_ >= less_than_ )
				throw std::invalid_argument( "moving_median_indicator: bigger_than value is bigger than less_than value" );
			mm_.reset( new moving_median_type( moving_median_window ) );
		}
		moving_median_indicator::~moving_median_indicator()
		{
		}
		void moving_median_indicator::process( const bar_type& b )
		{
			using namespace common::bar_data_types;
			common::bar_data::float_type price = 0.0;
			switch( data_type_in_use_ )
			{
			case open:
				price = b.open_;
				break;
			case high:
				price = b.high_;
				break;
			case low:
				price = b.low_;
				break;
			case close:
				price = b.close_;
				break;
			default:
				return;
			};
			mm_->add_element( price );
			if ( mm_->mature() )
			{
				const common::bar_data::float_type diff = price - mm_->get_median();
				if ( fabs( diff ) > bigger_than_  && fabs( diff ) < less_than_ )
				{
					const common::open_signal::side side = diff < 0 ? common::open_signal::side_long : common::open_signal::side_short;
					registrate_signal( b, new common::open_signal( side ) );
				}
			}
		}
	}
}
