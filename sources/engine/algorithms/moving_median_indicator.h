#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_

#include <boost/shared_ptr.hpp>

#include <bar_types.h>
#include <signal_types.h>

#include <algorithm_prototype.h>
#include <strategies_engine.h>

#include <algorithms/moving_median.h>


namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			class moving_median_indicator_tests;
		}
	}
	namespace engine
	{
		class moving_median_indicator : public on_stock_algorithm_prototype< common::open_signal >
		{
			friend class stsc::tests_::engine::moving_median_indicator_tests;

		private:
			typedef on_stock_algorithm_prototype< common::open_signal > base_type;

			stsc::engine::signal_vector< common::bar_data::float_type > moving_median_series_;

			const common::bar_data::float_type bigger_than_;
			const common::bar_data::float_type less_than_;
			
		public:
			explicit moving_median_indicator( const std::string& name,
											strategies_engine& se,
											const std::string& moving_median_subscription,
											const common::bar_data::float_type bigger_than,
											const common::bar_data::float_type less_than );
			~moving_median_indicator();

			virtual void process( const bar_type& b );
		};
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_

