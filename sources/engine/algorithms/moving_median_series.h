#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_

#include <common/bar_types.h>
#include <common/bar_data_adapter.h>

#include <algorithms_storage/on_stock_algorithm.h>
#include <series_storage/vector_serie.h>
#include <series_storage/map_serie.h>

#include <algorithms/moving_median.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms
			{
				class moving_median_series_test_helper;
				class moving_median_indicator_tests;
			}
		}
	}
	namespace engine
	{
		namespace algorithms
		{
			typedef algorithms_storage::on_stock_algorithm_init< size_t > moving_median_series_init;

			template< stsc::common::bar_data_type::value bar_data_element = stsc::common::bar_data_type::close >
			class moving_median_series : public algorithms_storage::on_stock_algorithm< stsc::common::bar_data::float_type >
			{
				friend class stsc::tests_::engine::algorithms::moving_median_series_test_helper;
				friend class stsc::tests_::engine::algorithms::moving_median_indicator_tests;

				typedef typename algorithms_storage::on_stock_algorithm< stsc::common::bar_data::float_type > base_class;
				typedef typename details::moving_median< stsc::common::bar_data::float_type > moving_median_type;

				moving_median_type mm_;
			public:
				explicit moving_median_series( const moving_median_series_init& init )
					: base_class( init, series_storage::create_vector_serie_ptr< signal_type >() )
					, mm_( init.parameters )
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
			};
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
