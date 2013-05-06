#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_

#include <string>
#include <sstream>

#include <boost/shared_ptr.hpp>

#include <common/bar_types.h>

#include <series_storage/map_serie.h>

#include <algorithms_storage/algorithm.h>
#include <algorithm_manager.h>


namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			namespace details
			{
				struct algorithm_init : public boost::noncopyable
				{
					const common::shared_string name;
					const algorithm_manager& manager;
					explicit algorithm_init( const common::shared_string& n, const algorithm_manager& m );
					explicit algorithm_init( const std::string& n, const algorithm_manager& m );
				};

				template< typename input_type, typename output_type >
				class algorithm_prototype : public algorithm_with_serie< output_type >
				{
					typedef algorithm_with_serie< output_type > base_class;
				protected:
					typedef typename input_type bar_type;

					const algorithm_manager& algorithms_;

					explicit algorithm_prototype( const algorithm_init& init, typed_serie_ptr& serie );
					explicit algorithm_prototype( const algorithm_init& init );
					virtual ~algorithm_prototype();
					//
					virtual void pre_process();
					//
					virtual void register_signal( const bar_type& b, const signal_type_ptr& signal );
					/// this method copy signal by copy constructor
					virtual void register_signal( const bar_type& b, const signal_type& signal );
					/// this method use boost::shared_ptr to store element - you should not call 'delete' for this pointer
					/// do not use .get() method to send signal here use appropriate method for storing signal in several places
					virtual void register_signal( const bar_type& b, signal_type* const signal );
				};

				template< typename input_type, typename output_type >
				algorithm_prototype< input_type, output_type >::algorithm_prototype( const algorithm_init& init, typed_serie_ptr& serie )
					: base_class( init.name, serie )
					, algorithms_( init.manager )
				{
				}
				template< typename input_type, typename output_type >
				algorithm_prototype< input_type, output_type >::algorithm_prototype( const algorithm_init& init )
					: base_class( init.name, series_storage::create_map_serie_ptr< signal_type >() )
					, algorithms_( init.manager )
				{
				}
				template< typename input_type, typename output_type >
				algorithm_prototype< input_type, output_type >::~algorithm_prototype()
				{
				}
				template< typename input_type, typename output_type >
				void algorithm_prototype< input_type, output_type >::pre_process()
				{
				}
				//
				template< typename input_type, typename output_type >
				void algorithm_prototype< input_type, output_type >::register_signal( const bar_type& b, const signal_type& signal )
				{
					register_signal( b, signal_type_ptr( new signal_type( signal ) ) );
				}
				template< typename input_type, typename output_type >
				void algorithm_prototype< input_type, output_type >::register_signal( const bar_type& b, signal_type* const signal )
				{
					register_signal( b, signal_type_ptr( signal ) );
				}
				template< typename input_type, typename output_type >
				void algorithm_prototype< input_type, output_type >::register_signal( const bar_type& b, const signal_type_ptr& signal )
				{
					serie_->insert( b.index, signal );
				}
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_
