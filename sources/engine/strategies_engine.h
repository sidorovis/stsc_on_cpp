#ifndef _STSC_ENGINE_STRATEGIES_ENGINE_H_
#define _STSC_ENGINE_STRATEGIES_ENGINE_H_

#include <boost/noncopyable.hpp>

#include <algorithms_storage.h>
#include <signals_storage.h>

namespace stsc
{
	namespace engine
	{
		class strategies_engine : protected boost::noncopyable
		{

			template< typename input_bar_type, typename output_signal_type >
			class algorithm_prototype;
			
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
			void registrate_on_stock_algorithm( details::algorithm_storage::const_pointer algorithm );
			void unregister_on_stock_algorithm( details::algorithm_storage::const_pointer algorithm );
			//
			void registrate_on_bar_algorithm( details::algorithm_storage::const_pointer algorithm );
			void unregistrate_on_bar_algorithm( details::algorithm_storage::const_pointer algorithm );
			//
			void registrate_on_period_algorithm( details::algorithm_storage::const_pointer algorithm );
			void unregistrate_on_period_algorithm( details::algorithm_storage::const_pointer algorithm );
		};
	}
}

#endif // _STSC_ENGINE_STRATEGIES_ENGINE_H_

