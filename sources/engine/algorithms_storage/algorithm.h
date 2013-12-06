#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_H_

#include <typeinfo> 
#include <string>

#include <common/bar_types.h>

#include <series_storage/serie.h>

#include <simulation_configuration.h>

namespace stsc
{
	namespace engine
	{
		class algorithm_manager;

		namespace algorithms_storage
		{
			class algorithm;

			typedef boost::shared_ptr< const algorithm > const_algorithm_ptr;
			typedef boost::shared_ptr< algorithm > algorithm_ptr;

			class algorithm
			{
			public:
				virtual ~algorithm();
				//
				virtual void subscription_check( const std::type_info& ti ) const = 0;
				virtual algorithm* copy() const = 0;
				virtual const common::shared_string& name() const = 0;
			};
			//
			template< typename bar_type >
			class algorithm_interface : virtual public algorithm
			{
			public:
				algorithm_interface(){}
				virtual ~algorithm_interface(){}
				virtual void process( const bar_type& b ) = 0;
				virtual void initialization( const details::execution_ptr& ptr, algorithm_manager& am ){}
			};
			//
			template< typename output_type >
			class algorithm_with_serie : virtual public algorithm
			{
				friend class algorithm_manager;
			private:
				static const std::type_info& signal_type_info_;
			protected:
				typedef typename output_type signal_type;
				typedef typename boost::shared_ptr< signal_type > signal_type_ptr;

				typedef series_storage::serie_ptr< signal_type > typed_serie_ptr;
				const common::shared_string name_;
				typed_serie_ptr serie_;
			protected:
				algorithm_with_serie( const algorithm_with_serie& other );
			public:
				explicit algorithm_with_serie(  const common::shared_string& name, typed_serie_ptr& serie );
				virtual ~algorithm_with_serie();
				//
				virtual void subscription_check( const std::type_info& ti ) const;
				virtual const common::shared_string& name() const;
			};
			template< typename signal_type >
			algorithm_with_serie<signal_type>::algorithm_with_serie( const common::shared_string& name, typed_serie_ptr& serie )
				: name_( name )
				, serie_( serie )
			{
			}

			template< typename signal_type >
			algorithm_with_serie<signal_type>::algorithm_with_serie( const algorithm_with_serie& other )
				: name_( other.name_ )
				, serie_( other.serie_ )
			{
			}

			template< typename signal_type >
			algorithm_with_serie<signal_type>::~algorithm_with_serie()
			{
			}
			//
			template< typename signal_type >
			const std::type_info& algorithm_with_serie< signal_type >::signal_type_info_ = typeid( signal_type );
			//
			template< typename signal_type >
			void algorithm_with_serie< signal_type >::subscription_check( const std::type_info& ti ) const
			{
				std::stringstream error_line;
				error_line << "algorithm signal type " << signal_type_info_.name() << " decline subscription on " << ti.name();
				if ( ti != signal_type_info_ )
					throw std::logic_error( error_line.str() );
			}
			//
			template< typename signal_type >
			const common::shared_string& algorithm_with_serie< signal_type >::name() const
			{
				return name_;
			}
			//
			template< typename algo_type >
			class typed_algorithm : public boost::shared_ptr< algo_type >
			{
			public:
				explicit typed_algorithm( algo_type* const algo )
					: boost::shared_ptr< algo_type >( algo )
				{
				}
			};
			//
			//
#define declare_copy_method(class_name) \
stsc::engine::algorithms_storage::algorithm* class_name::copy() const; \

#define generate_copy_method(class_name) \
stsc::engine::algorithms_storage::algorithm* class_name::copy() const \
{ \
	return new class_name( *this ); \
} \



		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_H_
