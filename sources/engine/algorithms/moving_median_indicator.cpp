#include <algorithms/moving_median_indicator.h>

#include <math.h>

#include <series_storage/map_serie.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms
		{
			moving_median_indicator::moving_median_indicator( const std::string& name )
				: base_type( name, series_storage::create_map_serie_ptr< signal_type >() )
			{
				if ( bigger_than_ >= less_than_ )
					throw std::invalid_argument( "moving_median_indicator: bigger_than value is bigger than less_than value" );
			}
			moving_median_indicator::~moving_median_indicator()
			{
			}
			void moving_median_indicator::initialization( const engine::details::execution_ptr& ptr, algorithm_manager& am )
			{
				bigger_than_ = ptr->parameter< float_type >( "bigger" );
				less_than_ = ptr->parameter< float_type >( "less" );
				moving_median_serie_ = am.subscribe< float_type >( ptr->used()[0] );
				//am.
			
//				moving_median_serie_ = algorithm_storage().
			}

			void moving_median_indicator::process( const bar_type& b )
			{
				serie_type::signal_type_const_ptr mmse = moving_median_serie_->ptr_at( b.index );
				if ( mmse )
				{
					const common::bar_data::float_type diff = b.value.close_ - *mmse;
					if ( fabs( diff ) > bigger_than_  && fabs( diff ) < less_than_ )
					{
						using common::open_signal;
						const open_signal::side side = ( diff < 0 ) ? open_signal::side_long : open_signal::side_short;
						register_signal( b, new open_signal( side ) );
					}
				}
			}
		}
	}
}
