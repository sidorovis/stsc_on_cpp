#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ON_STOCK_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ON_STOCK_ALGORITHM_H_

#include <algorithms_storage/algorithm_prototype.h>
#include <algorithm_manager.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			template< typename output_signal_type >
			class on_stock_algorithm : public algorithm_prototype< common::on_stock_bar, output_signal_type >
			{
				typedef typename algorithm_prototype< common::on_stock_bar, signal_type > base_class;
				common::shared_string stock_name_;
			protected:
				explicit on_stock_algorithm( const std::string& name, typed_serie_ptr& serie );
				virtual ~on_stock_algorithm();
				//
				//template< typename subscription_signal_type >
				//series_storage::const_serie_ptr< subscription_signal_type > subscribe( const std::string& subscription_name );
				//template< typename subscription_signal_type >
				//series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_bar( const std::string& subscription_name );
				//template< typename subscription_signal_type >
				//series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_period( const std::string& subscription_name );
			private:
				virtual void process( const bar_type& b ) = 0;
			};

			template< typename output_signal_type >
			on_stock_algorithm< output_signal_type >::on_stock_algorithm( const std::string& name, typed_serie_ptr& serie )
				: base_class( algorithm_storage().register_algorithm_name( name ), serie )
			{
				algorithm_storage().register_on_stock( name_, this );
			}
			template< typename output_signal_type >
			on_stock_algorithm< output_signal_type >::~on_stock_algorithm()
			{
			}
			
			//template< typename output_signal_type >
			//	template< typename subscription_signal_type >
			//series_storage::const_serie_ptr< subscription_signal_type > on_stock_algorithm< output_signal_type >::subscribe( const std::string& subscription_name )
			//{
			//	return algorithms_.subscribe_on_stock< subscription_signal_type >( subscription_name, stock_name_ );
			//}
			//template< typename output_signal_type >
			//	template< typename subscription_signal_type >
			//series_storage::const_serie_ptr< subscription_signal_type > on_stock_algorithm< output_signal_type >::subscribe_on_bar( const std::string& subscription_name )
			//{
			//	return algorithms_.subscribe_on_bar< subscription_signal_type >( subscription_name );
			//}
			//template< typename output_signal_type >
			//	template< typename subscription_signal_type >
			//series_storage::const_serie_ptr< subscription_signal_type > on_stock_algorithm< output_signal_type >::subscribe_on_period( const std::string& subscription_name )
			//{
			//	return algorithms_.subscribe_on_period< subscription_signal_type >( subscription_name );
			//}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ON_STOCK_ALGORITHM_H_
