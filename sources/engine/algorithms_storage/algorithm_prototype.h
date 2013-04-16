#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include <algorithms_storage/algorithm.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			namespace details
			{
				template< typename input_type, typename output_type >
				class algorithm_prototype : public algorithm
				{
				protected:
					typedef input_type bar_type;
					typedef output_type signal_type;
					typedef boost::shared_ptr< signal_type > signal_type_ptr;

				protected:
					explicit algorithm_prototype( const std::string& name );
					virtual ~algorithm_prototype();
					/// this method copy signal by copy constructor
					virtual void register_signal( const bar_type& b, const signal_type& signal );
					/// this method use boost::shared_ptr to store element - you should not call 'delete' for this pointer
					/// do not use .get() method to send signal here use appropriate method for storing signal in several places
					virtual void register_signal( const bar_type& b, signal_type* const signal );
					virtual void register_signal( const bar_type& b, const signal_type_ptr& signal ) = 0;
				};

				template< typename input_type, typename output_type >
				algorithm_prototype< input_type, output_type >::algorithm_prototype( const std::string& name )
					: algorithm( name )
				{
				}
				template< typename input_type, typename output_type >
				algorithm_prototype< input_type, output_type >::~algorithm_prototype()
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
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_
