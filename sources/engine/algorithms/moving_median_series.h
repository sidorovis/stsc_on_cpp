#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_

//#include <common/bar_types.h>
//#include <common/bar_data_adapter.h>

#include <algorithms_storage/on_stock_algorithm.h>
#include <series_storage/vector_serie.h>

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

			class moving_median_series : public algorithms_storage::on_stock_algorithm< stsc::common::bar_data::float_type >
			{
				friend class stsc::tests_::engine::algorithms::moving_median_series_test_helper;
				friend class stsc::tests_::engine::algorithms::moving_median_indicator_tests;

				typedef algorithms_storage::on_stock_algorithm< stsc::common::bar_data::float_type > base_class;
				typedef details::moving_median< stsc::common::bar_data::float_type > moving_median_type;

				boost::shared_ptr< moving_median_type > mm_;
			public:
				explicit moving_median_series( const std::string& name )
					: base_class( name, series_storage::create_vector_serie_ptr< signal_type >() )
				{
				}
				virtual ~moving_median_series()
				{
				}
				virtual void initialization( const engine::details::execution_ptr& ptr )
				{
					mm_.reset( new moving_median_type( ptr->parameter< size_t >( "window_size" ) ) );
				}
			private:
				virtual void process( const bar_type& b )
 				{
					mm_->add_element( b.value.close_ );
					if ( mm_->mature() )
						register_signal( b, mm_->get_median() );
				}
			public:
				generate_copy_method( moving_median_series )
			};
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
