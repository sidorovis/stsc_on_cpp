#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_

#include <boost/shared_ptr.hpp>

#include <common/bar_types.h>
#include <common/signal_types.h>

#include <algorithms_storage/on_stock_algorithm.h>

#include <algorithms/moving_median.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms
			{
				class moving_median_indicator_tests;
			}
		}
	}
	namespace engine
	{
		namespace algorithms
		{
			struct moving_median_indicator_init_data
			{
				typedef common::bar_data::float_type float_type;
				std::string moving_median_serie_id;
				float_type bigger_than;
				float_type less_than;

				moving_median_indicator_init_data( const std::string& serie_id, const float_type bigger, const float_type less );
			};

			class moving_median_indicator : public algorithms_storage::on_stock_algorithm< common::open_signal >
			{
				friend class stsc::tests_::engine::algorithms::moving_median_indicator_tests;

			public:
				typedef algorithms_storage::on_stock_algorithm_init< moving_median_indicator_init_data > init_type;
			private:
				typedef algorithms_storage::on_stock_algorithm< common::open_signal > base_type;
				typedef common::bar_data::float_type float_type;

				typedef series_storage::const_serie_ptr< float_type > serie_type;
				const serie_type moving_median_serie_;
				
				const float_type bigger_than_;
				const float_type less_than_;
				
			public:
				explicit moving_median_indicator( const init_type& init );
				virtual ~moving_median_indicator();

				virtual void process( const bar_type& b );
			};
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_

