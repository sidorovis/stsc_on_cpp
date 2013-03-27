#ifndef _STSC_ENGINE_ALGORITHM_PROTOTYPE_H_
#define _STSC_ENGINE_ALGORITHM_PROTOTYPE_H_

#include <bar_types.h>

#include <algorithm.h>

#include <signal_vector.h>
#include <signals_storage.h>

namespace stsc
{
	namespace engine
	{
		/// algorithm_prototype is a template for algorithms
		/// please inherit algorithm_prototype (at least algorithm_prototype< common::bar_type, void >) to create correct algortihms
		/// Attention, never delete signals that where created by algortihm, storage should delete it automatically
		/// see tests/algorithm_storage_tests/algorithm_examples.h to see algortihm examples

		namespace details
		{

			template< typename input_bar_type, typename output_signal_type >
			class algorithm_prototype : public algorithm
			{
			protected:
				typedef input_bar_type bar_type;
				typedef output_signal_type signal_type;
			private:
				details::signals_storage& signals_storage_;
				signal_vector< output_signal_type >& signals_;
			protected:
				explicit algorithm_prototype( const std::string& name, signals_storage& ss );
				virtual ~algorithm_prototype();
				//
				void registrate_signal( const bar_type& b, signal_type* const output_signal );
				//
				template< typename output_subscription_signal_type >
				const signal_vector< output_subscription_signal_type >& subscribe( const std::string& subscription_name );
			};

			template< typename input_bar_type, typename output_signal_type >
			algorithm_prototype< input_bar_type, output_signal_type >::algorithm_prototype( const std::string& name, details::signals_storage& ss )
				: algorithm( name )
				, signals_storage_( ss )
				, signals_( ss.create_vector< signal_type >( name ) )
			{
			}
			template< typename input_bar_type, typename output_signal_type >
			algorithm_prototype< input_bar_type, output_signal_type >::~algorithm_prototype()
			{
			}
			template< typename input_bar_type, typename output_signal_type >
			void algorithm_prototype< input_bar_type, output_signal_type >::registrate_signal( const bar_type& b, signal_type* const output_signal )
			{
				signals_.insert( &b, output_signal );
			}

			template< typename input_bar_type, typename output_signal_type >
			template< typename output_subscription_signal_type >
			const signal_vector< output_subscription_signal_type >&
				algorithm_prototype<input_bar_type, output_signal_type>::subscribe( const std::string& subscription_name )
			{
				return signals_storage_.subscribe< output_subscription_signal_type >( subscription_name );
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHM_PROTOTYPE_H_
