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
			class moving_median_indicator : public algorithms_storage::on_stock_algorithm< common::open_signal >
			{
				friend class stsc::tests_::engine::algorithms::moving_median_indicator_tests;

				typedef algorithms_storage::on_stock_algorithm< common::open_signal > base_type;
				typedef common::bar_data::float_type float_type;

				typedef series_storage::const_serie_ptr< float_type > serie_type;

				serie_type moving_median_serie_;
				
				float_type bigger_than_;
				float_type less_than_;
				
			public:
				explicit moving_median_indicator( const std::string& name );
				virtual ~moving_median_indicator();

				virtual void process( const bar_type& b );
				virtual void initialization( const engine::details::execution_ptr& ptr, algorithm_manager& am );

				declare_copy_method( moving_median_indicator );
			};
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_INDICATOR_H_

