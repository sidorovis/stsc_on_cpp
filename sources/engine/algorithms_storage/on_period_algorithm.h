#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ON_PERIOD_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ON_PERIOD_ALGORITHM_H_

#include <algorithms_storage/algorithm_init.h>
#include <algorithm_manager.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			template< typename output_signal_type >
			class on_period_algorithm : public details::algorithm_prototype< common::on_period, output_signal_type >
			{
				typedef typename algorithm_prototype< common::on_period, signal_type > base_class;
			protected:
				template< typename algorithm_init >
				explicit on_period_algorithm( const algorithm_init& init, typed_serie_ptr& serie );
				virtual ~on_period_algorithm();
			private:
				virtual void process( const bar_type& b ) = 0;

			protected:
				template< typename subscription_signal_type >
				series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_stock( const std::string& subscription_name, const std::string& stock_name );
				template< typename subscription_signal_type >
				series_storage::const_serie_ptr< subscription_signal_type > subscribe( const std::string& subscription_name );
				template< typename subscription_signal_type >
				series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_period( const std::string& subscription_name );
			};

			template< typename output_signal_type >
				template< typename algorithm_init >
			on_period_algorithm< output_signal_type >::on_period_algorithm( const algorithm_init& init, typed_serie_ptr& serie )
				: base_class( init, serie )
			{
			}
			template< typename output_signal_type >
			on_period_algorithm< output_signal_type >::~on_period_algorithm()
			{
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ON_PERIOD_ALGORITHM_H_
