#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ON_BAR_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ON_BAR_ALGORITHM_H_

#include <algorithms_storage/algorithm_prototype.h>
#include <algorithm_manager.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			template< typename output_signal_type >
			class on_bar_algorithm : public details::algorithm_prototype< common::on_bar, output_signal_type >
			{
				typedef typename algorithm_prototype< common::on_bar, signal_type > base_class;
			protected:
				explicit on_bar_algorithm( const details::algorithm_init& init, typed_serie_ptr& serie );
				virtual ~on_bar_algorithm();
			private:
				virtual void process( const bar_type& b ) = 0;
			};

			template< typename output_signal_type >
			on_bar_algorithm< output_signal_type >::on_bar_algorithm( const details::algorithm_init& init, typed_serie_ptr& serie )
				: base_class( init, serie )
			{
			}
			template< typename output_signal_type >
			on_bar_algorithm< output_signal_type >::~on_bar_algorithm()
			{
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ON_BAR_ALGORITHM_H_
