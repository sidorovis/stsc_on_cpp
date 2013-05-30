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

				typedef boost::shared_ptr< algorithms_storage::algorithm > algorithm_ptr;
				typedef std::map< common::shared_string, algorithm_ptr > algorithms;
				algorithms on_stock_algorithms_;
				algorithms on_bar_algorithms_;
				algorithms on_period_algorithms_;

				explicit algorithm_storage_instance();
			public:
				virtual ~algorithm_storage_instance();

				template< typename algorithm_type_ptr >
				common::shared_string register_on_stock( const std::string& algorithm_type_name, algorithm_type_ptr& algo );

				template< typename algorithm_type_ptr >
				common::shared_string register_on_bar( const std::string& algorithm_type_name, algorithm_type_ptr& algo );

				template< typename algorithm_type_ptr >
				common::shared_string register_on_period( const std::string& algorithm_type_name, algorithm_type_ptr& algo );

				template< typename algorithm_type_ptr >
				boost::shared_ptr< algorithm_type_ptr > on_stock_algorithm_prototype( const std::string& algorithm_type_name ) const;
				
			};

			template< typename algorithm_type_ptr >
			common::shared_string algorithm_storage_instance::register_on_stock( const std::string& algorithm_type_name, algorithm_type_ptr& algo )
			{
				algorithm_names_.add_name( algorithm_type_name );
				common::shared_string result = algorithm_names_.get_shared( algorithm_type_name );

				if ( !on_stock_algorithms_.insert( std::make_pair( result, algorithm_ptr( algo ) ) ).second )
					throw std::logic_error( "algorithm " + algorithm_type_name + " allready exists at on_stock algorithm_storage" );

				return result;
			}

			template< typename algorithm_type_ptr >
			common::shared_string algorithm_storage_instance::register_on_bar( const std::string& algorithm_type_name, algorithm_type_ptr& algo )
			{
				algorithm_names_.add_name( algorithm_type_name );
				common::shared_string result = algorithm_names_.get_shared( algorithm_type_name );

				if ( !on_bar_algorithms_.insert( std::make_pair( result, algorithm_ptr( algo ) ) ).second )
					throw std::logic_error( "algorithm " + algorithm_type_name + " allready exists at on_stock algorithm_storage" );

				return result;
			}

			template< typename algorithm_type_ptr >
			common::shared_string algorithm_storage_instance::register_on_period( const std::string& algorithm_type_name, algorithm_type_ptr& algo )
			{
				algorithm_names_.add_name( algorithm_type_name );
				common::shared_string result = algorithm_names_.get_shared( algorithm_type_name );

				if ( !on_period_algorithms_.insert( std::make_pair( result, algorithm_ptr( algo ) ) ).second )
					throw std::logic_error( "algorithm " + algorithm_type_name + " allready exists at on_stock algorithm_storage" );

				return result;
			}

			//template< typename algorithm_type_ptr >
			//boost::shared_ptr< algorithm_type_ptr > algorithm_storage_instance::create_algorithm( const std::string& algorithm_type_name ) const
			//{
			//	algorithms::const_iterator i = algorithms_.find( algorithm_names_.get_shared( algorithm_type_name ) );
			//	if ( i == algorithms_.end() )
			//		throw std::logic_error( "no such algorithm '" + algorithm_type_name + "' at storage, please check your code configuration" );
			//	boost::shared_ptr< algorithm_type > result;
			//	result.reset( dynamic_cast< algorithm_type_ptr >( i->copy() ) );
			//	return result;
			//}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHM_STORAGE_H_
