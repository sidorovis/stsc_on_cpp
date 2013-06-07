#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_

#include <string>
#include <sstream>

#include <boost/shared_ptr.hpp>

#include <common/bar_types.h>

#include <series_storage/map_serie.h>

#include <algorithms_storage/algorithm.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{

			template< typename input_type, typename output_type >
			class algorithm_prototype : public algorithm_with_serie< output_type >, public algorithm_interface< input_type >
			{
				typedef algorithm_with_serie< output_type > base_class;
				typedef algorithm_interface< input_type > base_interface;
			protected:	
				typedef typename input_type bar_type;

				explicit algorithm_prototype( const common::shared_string& name, typed_serie_ptr& serie );
				virtual ~algorithm_prototype();
				//
				virtual void register_signal( const bar_type& b, const signal_type_ptr& signal );
				/// this method copy signal by copy constructor
				virtual void register_signal( const bar_type& b, const signal_type& signal );
				/// this method use boost::shared_ptr to store element - you should not call 'delete' for this pointer
				/// do not use .get() method to send signal here use appropriate method for storing signal in several places
				virtual void register_signal( const bar_type& b, signal_type* const signal );
			public:
				virtual void subscription_check( const std::type_info& ti ) const;
				virtual const common::shared_string& name() const;
			};


			template< typename input_type, typename output_type >
			algorithm_prototype< input_type, output_type >::algorithm_prototype( const common::shared_string& name, typed_serie_ptr& serie )
				: algorithm()
				, base_class( name, serie )
				, base_interface()
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
			template< typename input_type, typename output_type >
			void algorithm_prototype< input_type, output_type >::register_signal( const bar_type& b, const signal_type_ptr& signal )
			{
				serie_->insert( b.index, signal );
			}
			//
			template< typename algorithm_type >
			algorithm_type* create_algorithm()
			{
				algorithm_type* result = new algorithm_type();
				return result;
			};
			template< typename algorithm_type, typename signal_serie_type >
			algorithm_type* create_algorithm( const std::string& name, signal_serie_type& serie )
			{
				algorithm_type* result = new algorithm_type( name, serie );
				return result;
			};
			template< typename algorithm_type >
			algorithm_type* create_algorithm( const std::string& name )
			{
				algorithm_type* result = new algorithm_type( name );
				return result;
			};
			template< typename algorithm_type >
			algorithm_type* create_algorithm( const std::string& name, const details::execution_ptr& ptr )
			{
				algorithm_type* result = new algorithm_type( name, ptr );
				return result;
			};

			//
			template< typename input_type, typename output_type >
			void algorithm_prototype< input_type, output_type >::subscription_check( const std::type_info& ti ) const
			{
				return base_class::subscription_check( ti );
			}
			template< typename input_type, typename output_type >
			const common::shared_string& algorithm_prototype< input_type, output_type >::name() const
			{
				return base_class::name();
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_PROTOTYPE_H_
