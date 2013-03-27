#ifndef _STSC_ENGINE_ON_PERIOD_ALGORITHM_PROTOTYPE_H_
#define _STSC_ENGINE_ON_PERIOD_ALGORITHM_PROTOTYPE_H_

#include <bar_types.h>
#include <algorithm_prototype.h>

#include <strategies_engine.h>

namespace stsc
{
	namespace engine
	{

		template< typename output_signal_type >
		class on_period_algorithm_prototype : public details::algorithm_prototype< common::bar_type, output_signal_type >
		{
			typedef typename algorithm_prototype< common::bar_type, output_signal_type > typed_algorithm;
			strategies_engine& strategies_engine_;

		protected:
			explicit on_period_algorithm_prototype( const std::string& name, strategies_engine& se );
			virtual ~on_period_algorithm_prototype();
		private:
			virtual void process( const bar_type& b ) = 0;
		};

		template< typename output_signal_type >
		on_period_algorithm_prototype< output_signal_type >::on_period_algorithm_prototype( const std::string& name, strategies_engine& se )
			: typed_algorithm( name, se.signals_storage_ )
			, strategies_engine_( se )
		{
			strategies_engine_.registrate_on_period_algorithm( this );
		}
		template< typename output_signal_type >
		on_period_algorithm_prototype< output_signal_type >::~on_period_algorithm_prototype()
		{
			strategies_engine_.unregistrate_on_period_algorithm( this );
		}

	}
}

#endif // _STSC_ENGINE_ON_PERIOD_ALGORITHM_PROTOTYPE_H_
