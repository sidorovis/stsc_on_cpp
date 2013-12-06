#ifndef _STSC_ENGINE_ALGORITHM_STORAGE_H_
#define _STSC_ENGINE_ALGORITHM_STORAGE_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <algorithms_storage/algorithm.h> 

namespace stsc
{
	namespace engine
	{
		class algorithm_manager;

		namespace details
		{
			class algorithm_storage_instance;
		}

		details::algorithm_storage_instance& algorithm_storage();

		namespace details
		{
			class algorithm_storage_instance : virtual public boost::noncopyable
			{
				friend class stsc::engine::algorithm_manager;
				friend stsc::engine::details::algorithm_storage_instance& stsc::engine::algorithm_storage();
			public:
				typedef system_utilities::common::shared_name_storage shared_name_storage;
			private:
				shared_name_storage algorithm_names_;

				typedef std::map< common::shared_string, algorithms_storage::const_algorithm_ptr > algorithms;
				algorithms on_stock_algorithms_;
				algorithms on_bar_algorithms_;
				algorithms on_period_algorithms_;

				explicit algorithm_storage_instance();
			public:
				virtual ~algorithm_storage_instance();

				void clear();

				common::shared_string register_algorithm_name( const std::string& algorithm_name );

				template< typename algorithm_type >
				void register_on_stock( const common::shared_string& algorithm_type_name, const algorithm_type* const algo );

				template< typename algorithm_type >
				void register_on_bar( const common::shared_string& algorithm_type_name, const algorithm_type* const algo );

				template< typename algorithm_type >
				void register_on_period( const common::shared_string& algorithm_type_name, const algorithm_type* const algo );

				//
				template< typename algorithm_type >
				algorithms_storage::typed_algorithm< algorithm_type > create_on_stock( const common::shared_string& algorithm_type_name ) const;
				template< typename algorithm_type >
				algorithms_storage::typed_algorithm< algorithm_type > create_on_stock( const std::string& algorithm_type_name ) const;
				//
				template< typename algorithm_type >
				algorithms_storage::typed_algorithm< algorithm_type > create_on_bar( const common::shared_string& algorithm_type_name ) const;
				template< typename algorithm_type >
				algorithms_storage::typed_algorithm< algorithm_type > create_on_bar( const std::string& algorithm_type_name ) const;
				//
				template< typename algorithm_type >
				algorithms_storage::typed_algorithm< algorithm_type > create_on_period( const common::shared_string& algorithm_type_name ) const;
				template< typename algorithm_type >
				algorithms_storage::typed_algorithm< algorithm_type > create_on_period( const std::string& algorithm_type_name ) const;
				
			};

			template< typename algorithm_type >
			void algorithm_storage_instance::register_on_stock( const common::shared_string& algorithm_type_name, const algorithm_type* const algo )
			{
				algorithms_storage::const_algorithm_ptr ptr( dynamic_cast< const algorithms_storage::algorithm* const >( algo ) );
				if ( !on_stock_algorithms_.insert( std::make_pair( algorithm_type_name, ptr ) ).second )
					throw std::logic_error( "algorithm " + *algorithm_type_name + " allready exists at on_stock algorithm_storage" );
			}

			template< typename algorithm_type >
			void algorithm_storage_instance::register_on_bar( const common::shared_string& algorithm_type_name, const algorithm_type* const algo )
			{
				algorithms_storage::const_algorithm_ptr ptr( dynamic_cast< const algorithms_storage::algorithm* const >( algo ) );
				if ( !on_bar_algorithms_.insert( std::make_pair( algorithm_type_name, ptr ) ).second )
					throw std::logic_error( "algorithm " + *algorithm_type_name + " allready exists at on_stock algorithm_storage" );
			}

			template< typename algorithm_type >
			void algorithm_storage_instance::register_on_period( const common::shared_string& algorithm_type_name, const algorithm_type* const algo )
			{
				algorithms_storage::const_algorithm_ptr ptr( dynamic_cast< const algorithms_storage::algorithm* const >( algo ) );
				if ( !on_period_algorithms_.insert( std::make_pair( algorithm_type_name, ptr ) ).second )
					throw std::logic_error( "algorithm " + *algorithm_type_name + " allready exists at on_stock algorithm_storage" );
			}
			//
			template< typename algorithm_type >
			algorithms_storage::typed_algorithm< algorithm_type > algorithm_storage_instance::create_on_stock( const common::shared_string& algorithm_type_name ) const
			{
				algorithms::const_iterator i = on_stock_algorithms_.find( algorithm_type_name );

				if ( i == on_stock_algorithms_.end() )
					throw std::logic_error( "trying to use stock algorithm " + *algorithm_type_name + " without creating it" );

				algorithms_storage::typed_algorithm< algorithm_type > result( dynamic_cast< algorithm_type* const >( i->second->copy() ) );
				if ( !result )
					throw std::logic_error( "algorithm " + *algorithm_type_name + " cannot be processed to " + typeid( algorithm_type ).name() );

				return result;
			}
			template< typename algorithm_type >
			algorithms_storage::typed_algorithm< algorithm_type > algorithm_storage_instance::create_on_stock( const std::string& algorithm_type_name ) const
			{
				const common::shared_string name = algorithm_names_.get_shared( algorithm_type_name );
				return create_on_stock< algorithm_type >( name );
			}
			template< typename algorithm_type >
			//
			algorithms_storage::typed_algorithm< algorithm_type > algorithm_storage_instance::create_on_bar( const common::shared_string& algorithm_type_name ) const
			{
				algorithms::const_iterator i = on_bar_algorithms_.find( algorithm_type_name );

				if ( i == on_bar_algorithms_.end() )
					throw std::logic_error( "trying to use bar algorithm " + *algorithm_type_name + " without creating it" );

				algorithms_storage::typed_algorithm< algorithm_type > result( dynamic_cast< algorithm_type* const >( i->second->copy() ) );
				if ( !result )
					throw std::logic_error( "algorithm " + *algorithm_type_name + " cannot be processed to " + typeid( algorithm_type ).name() );

				return result;
			}
			template< typename algorithm_type >
			algorithms_storage::typed_algorithm< algorithm_type > algorithm_storage_instance::create_on_bar( const std::string& algorithm_type_name ) const
			{
				const common::shared_string name = algorithm_names_.get_shared( algorithm_type_name );
				return create_on_bar< algorithm_type >( name );
			}
			//
			template< typename algorithm_type >
			algorithms_storage::typed_algorithm< algorithm_type > algorithm_storage_instance::create_on_period( const common::shared_string& algorithm_type_name ) const
			{
				algorithms::const_iterator i = on_period_algorithms_.find( algorithm_type_name );

				if ( i == on_period_algorithms_.end() )
					throw std::logic_error( "trying to use period algorithm " + *algorithm_type_name + " without creating it" );

				algorithms_storage::typed_algorithm< algorithm_type > result( dynamic_cast< algorithm_type* const >( i->second->copy() ) );
				if ( !result )
					throw std::logic_error( "algorithm " + *algorithm_type_name + " cannot be processed to " + typeid( algorithm_type ).name() );

				return result;
			}
			template< typename algorithm_type >
			algorithms_storage::typed_algorithm< algorithm_type > algorithm_storage_instance::create_on_period( const std::string& algorithm_type_name ) const
			{
				const common::shared_string name = algorithm_names_.get_shared( algorithm_type_name );
				return create_on_period< algorithm_type >( name );
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHM_STORAGE_H_
