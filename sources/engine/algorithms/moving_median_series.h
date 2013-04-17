#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_

#include <bar_types.h>
#include <bar_data_adapter.h>

#include <algorithms_storage/on_stock_algorithm.h>
#include <series_storage/vector_serie.h>
#include <series_storage/map_serie.h>

#include <algorithms/moving_median.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms
		{
			template< stsc::common::bar_data_type::value bar_data_element = stsc::common::bar_data_type::close >
			class moving_median_series : public algorithms_storage::on_stock_algorithm< stsc::common::bar_data::float_type >
			{
				typedef typename algorithms_storage::on_stock_algorithm< stsc::common::bar_data::float_type > base_class;
				typedef typename details::moving_median< stsc::common::bar_data::float_type > moving_median_type;

				moving_median_type mm_;
			public:
				explicit moving_median_series( const std::string& name, const size_t window )
					: base_class( name )
					, mm_( window )
				{
				}
				virtual ~moving_median_series()
				{
				}
			private:
				virtual void process( const bar_type& b )
				{
					typedef stsc::common::bar_data_adapter< bar_data_element > data_adapter;

					mm_.add_element( data_adapter::get( b.value ) );
					if ( mm_.mature() )
						register_signal( b, mm_.get_median() );
				}
				virtual serie_ptr serie_prototype() const
				{
					return base_class::serie_ptr( new stsc::engine::series_storage::vector_serie< signal_type >() );
				}
			};
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
