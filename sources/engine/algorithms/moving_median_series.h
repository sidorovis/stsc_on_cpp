#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_

#include <bar_types.h>
#include <bar_data_adapter.h>

#include <on_stock_algorithm_prototype.h>
#include <strategies_engine.h>

#include <algorithms/moving_median.h>

namespace stsc
{
	namespace engine
	{
		template< stsc::common::bar_data_type::value T = stsc::common::bar_data_type::close >
		class moving_median_series : public on_stock_algorithm_prototype< stsc::common::bar_data::float_type >
		{
		public:
			typedef on_stock_algorithm_prototype< stsc::common::bar_data::float_type > base_class;
			typedef moving_median< common::bar_data::float_type > moving_median_type;
			typedef boost::shared_ptr< moving_median_type > moving_median_ptr;

		private:
			moving_median_ptr mm_;

		public:
			explicit moving_median_series( const std::string& name,
											strategies_engine& se,
											const size_t moving_median_window )
											
				: base_class( name, se )
			{
				mm_.reset( new moving_median_type( moving_median_window ) );
			}
			~moving_median_series()
			{
			}
			virtual void process( const bar_type& b )
			{
				using namespace stsc::common;
				mm_->add_element( bar_data_adapter< T >::get( b ) );
				if ( mm_->mature() )
					registrate_signal( b, new bar_data::float_type( mm_->get_median() ) );
			}
		};
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_SERIES_H_
