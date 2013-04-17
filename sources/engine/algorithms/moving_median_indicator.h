#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_

#include <boost/shared_ptr.hpp>

#include <bar_types.h>
#include <signal_types.h>

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
			class moving_median_indicator : public algorithms_storage::on_stock_algorithm< common::open_signal >
			{
				friend class stsc::tests_::engine::algorithms::moving_median_indicator_tests;

			private:
				typedef algorithms_storage::on_stock_algorithm< common::open_signal > base_type;

				typedef common::bar_data::float_type float_type;

				const float_type bigger_than_;
				const float_type less_than_;
				
			public:
				explicit moving_median_indicator( const std::string& name, const float_type bigger_than, const float_type less_than );
				virtual ~moving_median_indicator();

				virtual void process( const bar_type& b );
			};
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_

