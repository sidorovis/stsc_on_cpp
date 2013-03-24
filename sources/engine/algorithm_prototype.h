#ifndef _STSC_ENGINE_ALGORITHM_ALGORITHM_PROTOTYPE_H_
#define _STSC_ENGINE_ALGORITHM_ALGORITHM_PROTOTYPE_H_

#include <string>
#include <boost/noncopyable.hpp>

#include <signals_storage.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			struct algorithm_storage;
		};
		class strategies_engine; 
		//

		class algorithm
		{
		public:
			virtual ~algorithm();
		};

		// algorithm_prototype is a template for algorithms
		// please inherit algorithm_prototype (at least algorithm_prototype< common::bar_type, void >) to create correct algortihms
		// Attention, never delete signals that where created by algortihm, storage should delete it automatically
		// see tests/algorithm_storage_tests/algorithm_examples.h to see algortihm examples
		//
		// 

		namespace details
		{
			template< typename input_bar_type, typename output_signal_type >
			class algorithm_prototype : public algorithm
			{
				friend struct details::algorithm_storage;
				friend class strategies_engine;
			public:
				typedef input_bar_type bar_type;
				typedef output_signal_type signal_type;
			private:
				const std::string name_;

				signal_vector< output_signal_type >& signals_;

			protected:
				explicit algorithm_prototype( const std::string& name, details::signals_storage& ss )
					: name_( name )
					, signals_( ss.create_vector< signal_type >( name ) )
				{
				}
				virtual ~algorithm_prototype()
				{
				}
				
			protected:
				void registrate_signal( const bar_type& b, signal_type* const output_signal )
				{
					signals_.insert( &b, output_signal );
				}
			};
		}


		template< typename output_signal_type >
		class on_stock_algorithm_prototype : public details::algorithm_prototype< common::price_bar, output_signal_type >
		{
			typedef typename algorithm_prototype< common::price_bar, output_signal_type > typed_algorithm;
			strategies_engine& strategies_engine_;

		protected:
			explicit on_stock_algorithm_prototype( const std::string& name, strategies_engine& se )
				: typed_algorithm( name, se.signals_storage_ )
				, strategies_engine_( se )
			{
				strategies_engine_.registrate_on_stock_algorithm( this );
			}
			virtual ~on_stock_algorithm_prototype()
			{
				strategies_engine_.unregister_on_stock_algorithm( this );
			}
		private:
			virtual void process( const bar_type& b ) = 0;
		};
		template< typename output_signal_type >
		class on_bar_algorithm_prototype : public details::algorithm_prototype< common::bar_type, output_signal_type >
		{
			typedef algorithm_prototype< common::bar_type, output_signal_type > typed_algorithm;
			strategies_engine& strategies_engine_;

		protected:
			explicit on_bar_algorithm_prototype( const std::string& name, stsc::engine::strategies_engine& se )
				: typed_algorithm( name, se.signals_storage_ )
				, strategies_engine_( se )
			{
				strategies_engine_.registrate_on_bar_algorithm( this );
			}
			virtual ~on_bar_algorithm_prototype()
			{
				strategies_engine_.unregistrate_on_bar_algorithm( this );
			}
		private:
			virtual void process( const bar_type& b ) = 0;
		};
		
		template< typename output_signal_type >
		class on_period_algorithm_prototype : public details::algorithm_prototype< common::bar_type, output_signal_type >
		{
			typedef algorithm_prototype< common::bar_type, output_signal_type > typed_algorithm;
			strategies_engine& strategies_engine_;
		protected:
			explicit on_period_algorithm_prototype( const std::string& name, stsc::engine::strategies_engine& se )
				: typed_algorithm( name, se.signals_storage_ )
				, strategies_engine_( se )
			{
				strategies_engine_.registrate_on_period_algorithm( this );
			}
			virtual ~on_period_algorithm_prototype()
			{
				strategies_engine_.unregistrate_on_period_algorithm( this );
			}
		private:
			virtual void process( const bar_type& b ) = 0;
		};
	}
}

#endif // _STSC_ENGINE_ALGORITHM_ALGORITHM_PROTOTYPE_H_
