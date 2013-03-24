#ifndef _STSC_ALGORITHM_STORAGE_STRATEGIES_ENGINE_H_
#define _STSC_ALGORITHM_STORAGE_STRATEGIES_ENGINE_H_

#include <boost/noncopyable.hpp>

#include <algorithm_storage.h>
#include <signals_storage.h>
#include <algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		class strategies_engine : protected boost::noncopyable
		{
			template< typename output_signal_type >
			friend class on_stock_algorithm_prototype;

			template< typename output_signal_type >
			friend class on_bar_algorithm_prototype;

			template< typename output_signal_type >
			friend class on_period_algorithm_prototype;

			details::algorithm_storage on_stock_algorithm_storage_;
			details::algorithm_storage on_bar_algorithm_storage_;
			details::algorithm_storage on_period_algorithm_storage_;

			details::signals_storage signals_storage_;
		public:
			explicit strategies_engine();
			~strategies_engine();
			//
		private:
			template< typename output_signal_type >
			void registrate_on_stock_algorithm( on_stock_algorithm_prototype< output_signal_type >* const algorithm )
			{
				on_stock_algorithm_storage_.insert( algorithm );
			}
			template< typename output_signal_type >
			void unregister_on_stock_algorithm( on_stock_algorithm_prototype< output_signal_type >* const algorithm )
			{
				on_stock_algorithm_storage_.erase( algorithm );
			}
			//
			template< typename output_signal_type >
			void registrate_on_bar_algorithm( on_bar_algorithm_prototype< output_signal_type >* const algorithm )
			{
				on_bar_algorithm_storage_.insert( algorithm );
			}
			template< typename output_signal_type >
			void unregistrate_on_bar_algorithm( on_bar_algorithm_prototype< output_signal_type >* const algorithm )
			{
				on_bar_algorithm_storage_.erase( algorithm );
			}
			//
			template< typename output_signal_type >
			void registrate_on_period_algorithm( on_period_algorithm_prototype< output_signal_type >* const algorithm )
			{
				on_period_algorithm_storage_.insert( algorithm );
			}
			template< typename output_signal_type >
			void unregistrate_on_period_algorithm( on_period_algorithm_prototype< output_signal_type >* const algorithm )
			{
				on_period_algorithm_storage_.erase( algorithm );
			}
			//
		public:
			template< typename output_signal_type >
			const signal_vector< output_signal_type >& subscribe( const std::string& name )
			{
				return signals_storage_.subscribe< output_signal_type >( name );
			}
		};
	}
}

#endif // _STSC_ALGORITHM_STORAGE_STRATEGIES_ENGINE_H_

