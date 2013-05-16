#ifndef _STSC_ENGINE_ALGORITHM_MANAGER_H_
#define _STSC_ENGINE_ALGORITHM_MANAGER_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <shared_name_storage.h>

#include <algorithms_storage/algorithm.h>

namespace stsc
{
	namespace engine
	{
		class algorithm_manager : virtual public boost::noncopyable
		{
			friend class stsc::engine::algorithms_storage::details::algorithm;

			typedef system_utilities::common::shared_name_storage shared_name_storage;
			shared_name_storage algorithm_names_;
			const shared_name_storage& stock_names_;
		public:
			typedef algorithms_storage::details::algorithm algorithm;
			typedef boost::shared_ptr< algorithm > algorithm_ptr;

			typedef std::map< common::shared_string, algorithm_ptr > algorithms;
			typedef algorithms::const_iterator const_iterator;
			typedef std::pair< const_iterator, const_iterator > on_stock_algorithm_sequence;
		private:
			typedef std::map< common::shared_string, algorithms > on_stock_algorithms;

			on_stock_algorithms on_stock_algorithms_;
			algorithms on_bar_algorithms_;
			algorithms on_period_algorithms_;

			typedef common::shared_string shared_string;

		public:
			explicit algorithm_manager( const shared_name_storage& stock_names );
			virtual ~algorithm_manager();
			//
			template< typename algorithm_type, typename init_type >
			on_stock_algorithm_sequence create_on_stock_algorithm( const std::string& algorithm_name, const init_type& init );
			//
			template< typename algorithm_type, typename init_type >
			algorithm_ptr create_on_bar_algorithm( const std::string& algorithm_name, const init_type& init );
			//
			template< typename algorithm_type, typename init_type >
			algorithm_ptr create_on_period_algorithm( const std::string& algorithm_name, const init_type& init );
			//
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_stock( const shared_string& subscription_name, const shared_string& stock_name ) const;
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_stock( const std::string& subscription_name, const shared_string& stock_name ) const;
			//
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_bar( const shared_string& subscription_name ) const;
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_bar( const std::string& subscription_name ) const;
			//
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_period( const shared_string& subscription_name ) const;
			template< typename subscription_signal_type >
			series_storage::const_serie_ptr< subscription_signal_type > subscribe_on_period( const std::string& subscription_name ) const;
			//
			void clear();
		};
		//
		template< typename algorithm_type, typename init_type >
		algorithm_manager::on_stock_algorithm_sequence algorithm_manager::create_on_stock_algorithm( const std::string& algorithm_name, const init_type& init )
		{
			if ( !algorithm_names_.add_name( algorithm_name ) )
				throw std::logic_error( "on stock algorithm name '" + algorithm_name + "' had been added before" );
			const common::shared_string& shared_algo_name = algorithm_names_.get_shared( algorithm_name );
			on_stock_algorithm_init< typename init_type > initialization( shared_algo_name, *this, init );

			for( shared_name_storage::const_iterator i = stock_names_.begin() ; i != stock_names_.end() ; ++i )
			{
				initialization.stock_name = i.shared();
				algorithm_ptr ptr( new algorithm_type( initialization ) );
				on_stock_algorithms_[ shared_algo_name ][ initialization.stock_name ] = ptr;
			}
			return on_stock_algorithm_sequence( on_stock_algorithms_[ shared_algo_name ].begin(), on_stock_algorithms_[ shared_algo_name ].end() );
		}
		//
		template< typename algorithm_type, typename init_type >
		algorithm_manager::algorithm_ptr algorithm_manager::create_on_bar_algorithm( const std::string& algorithm_name, const init_type& init )
		{
			if ( !algorithm_names_.add_name( algorithm_name ) )
				throw std::logic_error( "on bar algorithm name '" + algorithm_name + "' had been added before" );
			const common::shared_string& shared_algo_name = algorithm_names_.get_shared( algorithm_name );
			on_stock_algorithm_init< typename init_type > initialization( shared_algo_name, *this, init );

			algorithm_ptr ptr( new algorithm_type( initialization ) );
			on_bar_algorithms_[ shared_algo_name ] = ptr;
			return ptr;
		}
		//
		template< typename algorithm_type, typename init_type >
		algorithm_manager::algorithm_ptr algorithm_manager::create_on_period_algorithm( const std::string& algorithm_name, const init_type& init )
		{
			if ( !algorithm_names_.add_name( algorithm_name ) )
				throw std::logic_error( "on period algorithm name '" + algorithm_name + "' had been added before" );
			const common::shared_string& shared_algo_name = algorithm_names_.get_shared( algorithm_name );
			on_stock_algorithm_init< typename init_type > initialization( shared_algo_name, *this, init );

			algorithm_ptr ptr( new algorithm_type( initialization ) );
			on_period_algorithms_[ shared_algo_name ] = ptr;
			return ptr;
		}
		//
		template< typename subscription_signal_type >
		series_storage::const_serie_ptr< subscription_signal_type > algorithm_manager::subscribe_on_stock( const shared_string& subscription_name, const shared_string& stock_name ) const
		{
			on_stock_algorithms::const_iterator on_stock = on_stock_algorithms_.find( subscription_name );
			if ( on_stock == on_stock_algorithms_.end() )
				throw std::logic_error( "subscription on unknown on_stock algorithm " + *subscription_name );
			algorithms::const_iterator algo_iter = on_stock->second.find( stock_name );
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
		template< typename subscription_signal_type >
		series_storage::const_serie_ptr< subscription_signal_type > algorithm_manager::subscribe_on_bar( const shared_string& subscription_name ) const
		{
			algorithms::const_iterator on_bar = on_bar_algorithms_.find( subscription_name );
			if ( on_bar == on_bar_algorithms_.end() )
				throw std::logic_error( "subscription on unknown on_bar algorithm " + *subscription_name ); 
			const algorithm& algo = *(on_bar->second);
			algo.subscription_check( typeid( subscription_signal_type ) );
			typedef typename algorithms_storage::details::algorithm_with_serie< subscription_signal_type > typed_algorithm;
			const typed_algorithm& typed_algo = dynamic_cast< const typed_algorithm& >( algo );
			return series_storage::const_serie_ptr< subscription_signal_type >( typed_algo.serie_ );
		}
		template< typename subscription_signal_type >
		series_storage::const_serie_ptr< subscription_signal_type > algorithm_manager::subscribe_on_bar( const std::string& subscription_name ) const
		{
			const common::shared_string subs_shared = algorithm_names_.get_shared( subscription_name );
			return algorithm_manager::subscribe_on_bar< subscription_signal_type >( subs_shared );
		}
		//
		template< typename subscription_signal_type >
		series_storage::const_serie_ptr< subscription_signal_type > algorithm_manager::subscribe_on_period( const shared_string& subscription_name ) const
		{
			algorithms::const_iterator on_period = on_period_algorithms_.find( subscription_name );
			if ( on_period == on_period_algorithms_.end() )
				throw std::logic_error( "subscription on unknown on_bar algorithm " + *subscription_name ); 
			const algorithm& algo = *(on_period->second);
			algo.subscription_check( typeid( subscription_signal_type ) );
			typedef typename algorithms_storage::details::algorithm_with_serie< subscription_signal_type > typed_algorithm;
			const typed_algorithm& typed_algo = dynamic_cast< const typed_algorithm& >( algo );
			return series_storage::const_serie_ptr< subscription_signal_type >( typed_algo.serie_ );
		}
		template< typename subscription_signal_type >
		series_storage::const_serie_ptr< subscription_signal_type > algorithm_manager::subscribe_on_period( const std::string& subscription_name ) const
		{
			const common::shared_string subs_shared = algorithm_names_.get_shared( subscription_name );
			return algorithm_manager::subscribe_on_bar< subscription_signal_type >( subs_shared );
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHM_MANAGER_H_
