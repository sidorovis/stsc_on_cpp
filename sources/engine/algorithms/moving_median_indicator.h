#ifndef _STSC_ENGINE_ALGORITHM_ALGORITHM_MOVING_MEDIAN_INDICATOR_H_
#define _STSC_ENGINE_ALGORITHM_ALGORITHM_MOVING_MEDIAN_INDICATOR_H_

#include <boost/shared_ptr.hpp>

#include <algorithm_prototype.h>
#include <bar_types.h>
#include <signal_types.h>
#include <algorithms\moving_median.h>

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
			const common::bar_data_types::value data_type_in_use_;

			typedef moving_median< common::bar_data::float_type > moving_median_type;
			typedef boost::shared_ptr< moving_median_type > moving_median_ptr;
			moving_median_ptr mm_;
			const common::bar_data::float_type bigger_than_;
			const common::bar_data::float_type less_than_;
			
		public:
			explicit moving_median_indicator( const std::string& name, 
											strategies_engine& se, 
											const size_t moving_median_window,
											const common::bar_data::float_type bigger_than,
											const common::bar_data::float_type less_than,
											const common::bar_data_types::value type = common::bar_data_types::close );
			~moving_median_indicator();

			virtual void process( const bar_type& b );
		};
	}
}

#endif // _STSC_ENGINE_ALGORITHM_ALGORITHM_MOVING_MEDIAN_INDICATOR_H_

