#ifndef _STSC_ENGINE_ALGORITHM_MANAGER_H_
#define _STSC_ENGINE_ALGORITHM_MANAGER_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <bar_types.h>

#include <shared_name_storage.h>

#include <series_storage/serie.h>

#include <algorithms_storage/algorithm.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			namespace details
			{
				class algorithm;
			}
		}

		class algorithm_manager : virtual public boost::noncopyable
		{
			friend class stsc::engine::algorithms_storage::details::algorithm;

			typedef algorithms_storage::details::algorithm algorithm;
			typedef boost::shared_ptr< algorithm > algorithm_ptr;

			typedef system_utilities::common::shared_name_storage shared_name_storage;
			shared_name_storage algorithm_names_;
			shared_name_storage stock_names_;

			typedef std::map< common::shared_string, algorithm_ptr > stock_algorithms;
			typedef std::map< common::shared_string, stock_algorithms > on_stock_algorithms;

			typedef std::map< common::shared_string, algorithm_ptr > algorithms;

			on_stock_algorithms on_stock_algorithms_;
			algorithms on_bar_algorithms_;
			algorithms on_period_algorithms_;

			typedef common::shared_string shared_string;

		public:
			explicit algorithm_manager();
			virtual ~algorithm_manager();
			//
			template< typename iterator_type >
			void add_stocks( const iterator_type from, const iterator_type to );
			//
			template< typename algorithm_type, typename init_type >
			void create_on_stock_algorithm( const std::string& algorithm_name, const init_type& init );
			//
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_stock( const shared_string& subscription_name, const shared_string& stock_name ) const;
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_stock( const std::string& subscription_name, const shared_string& stock_name ) const;
		};
		//
		template< typename iterator_type >
		void algorithm_manager::add_stocks( const iterator_type from, const iterator_type to )
		{
			for( iterator_type i = from ; i != to ; ++i )
				stock_names_ << *i;
		}
		//
		template< typename algorithm_type, typename init_type >
		void algorithm_manager::create_on_stock_algorithm( const std::string& algorithm_name, const init_type& init )
		{
			if ( !algorithm_names_.add_name( algorithm_name ) )
				throw std::logic_error( "algorithm name '" + algorithm_name + "' had been added before" );
			const common::shared_string& shared_algo_name = algorithm_names_.get_shared( algorithm_name );
			on_stock_algorithm_init< typename init_type > initialization( shared_algo_name, *this, init );

			for( shared_name_storage::const_iterator i = stock_names_.begin() ; i != stock_names_.end() ; ++i )
			{
				initialization.stock_name = i.shared();
				algorithm_ptr ptr( new algorithm_type( initialization ) );
				on_stock_algorithms_[ shared_algo_name ][ initialization.stock_name ] = ptr;
			}
		}

		//
		template< typename subscription_signal_type >
		series_storage::const_serie_ptr< subscription_signal_type > algorithm_manager::subscribe_on_stock( const shared_string& subscription_name, const shared_string& stock_name ) const
		{
			on_stock_algorithms::const_iterator on_stock = on_stock_algorithms_.find( subscription_name );
			if ( on_stock == on_stock_algorithms_.end() )
				throw std::logic_error( "subscription on unknown on_stock algorithm " + *subscription_name );
			stock_algorithms::const_iterator algo_iter = on_stock->second.find( stock_name );
			if ( algo_iter == on_stock->second.end() )
				throw std::logic_error( "subscription on unknown on_stock algorithm " + *subscription_name + " on stock " + *stock_name );
			const algorithm& algo = *( algo_iter->second );
			algo.subscription_check( typeid( subscription_signal_type ) );
			typedef typename algorithms_storage::details::algorithm_with_serie< subscription_signal_type > typed_algorithm;
			const typed_algorithm& typed_algo = dynamic_cast< const typed_algorithm& >( algo );
			return series_storage::const_serie_ptr< subscription_signal_type >( typed_algo.serie_ );
		}
		template< typename subscription_signal_type >
		series_storage::const_serie_ptr< subscription_signal_type > algorithm_manager::subscribe_on_stock( const std::string& subscription_name, const shared_string& stock_name ) const
		{
			const common::shared_string subs_shared = algorithm_names_.get_shared( subscription_name );
			return algorithm_manager::subscribe_on_stock< subscription_signal_type >( subs_shared, stock_name );
		}
		//
	}
}

#endif // _STSC_ENGINE_ALGORITHM_MANAGER_H_
