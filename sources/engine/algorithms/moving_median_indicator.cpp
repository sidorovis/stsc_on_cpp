#include <algorithms/moving_median_indicator.h>

#include <math.h>

#include <series_storage/map_serie.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms
		{

			moving_median_indicator_init_data::moving_median_indicator_init_data( const std::string& serie_id, const float_type bigger, const float_type less )
				: moving_median_serie_id( serie_id )
				, bigger_than( bigger )
				, less_than( less )
			{
			}

			moving_median_indicator::moving_median_indicator( const init_type& init )
				: base_type( init, series_storage::create_map_serie_ptr< signal_type >() )
				, moving_median_serie_( subscribe< float_type >( init.parameters.moving_median_serie_id ) )
				, bigger_than_( init.parameters.bigger_than )
				, less_than_( init.parameters.less_than )
			{
				if ( bigger_than_ >= less_than_ )
					throw std::invalid_argument( "moving_median_indicator: bigger_than value is bigger than less_than value" );
			}
			moving_median_indicator::~moving_median_indicator()
			{
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
