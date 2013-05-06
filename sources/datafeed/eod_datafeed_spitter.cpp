#include <eod_datafeed_spitter.h>

#include <fstream>

#include <boost/thread.hpp>

#include <binary/reader.h>

#include <eod_datafeed_storage.h>

namespace stsc
{
	namespace datafeed
	{
		eod_datafeed_spitter_manager::eod_datafeed_spitter_manager()
		{
		}
		eod_datafeed_spitter_manager::~eod_datafeed_spitter_manager()
		{
		}
		void eod_datafeed_spitter_manager::on_stock( const common::shared_string& name, const common::on_stock_bar& bar )
		{
		}
		void eod_datafeed_spitter_manager::on_bar( const common::on_bar& bar )
		{
		}
		void eod_datafeed_spitter_manager::on_period( const common::on_period& bar )
		{
		}
		//
		eod_datafeed_spitter::eod_datafeed_spitter( eod_datafeed_spitter_manager& m, eod_datafeed_storage& storage )
			: manager_( m )
		{
			storage.datafeed_.swap( datafeed_ );
		}
		eod_datafeed_spitter::~eod_datafeed_spitter()
		{
		}
		//
		void eod_datafeed_spitter::spit_datafeed()
		{
			if ( datafeed_.empty() )
				return;
			while ( !datafeed_.empty() )
			{
				const long processing_date = datafeed_.begin()->first;
				sorted_datafeed::const_iterator start = datafeed_.lower_bound( processing_date );
				sorted_datafeed::const_iterator end = datafeed_.upper_bound( processing_date );

				if ( start != end )
				{
					const common::on_bar last_day_bar = start->second->create_on_bar();
					on_period_bar_ = start->second->create_on_period();
					
					for ( sorted_datafeed::const_iterator i = start ; i != end ; ++i )
					{
						manager_.on_stock( i->second->stock_name, i->second->create_on_stock_bar() );
						i->second->increment();
						elements_to_delete_insert_.push_back( i->second );
					}
					datafeed_.erase( processing_date );
					add_next_day_();

					manager_.on_bar( last_day_bar );
				}
				else
					datafeed_.erase( processing_date );
			}
			
			manager_.on_period( on_period_bar_ );
		}
		void eod_datafeed_spitter::multithread_spit_datafeed( const size_t thread_amount )
		{
			if ( datafeed_.empty() )
				return;

			boost::thread_group tg;
			for( size_t i = 0 ; i < thread_amount ; ++i )
				tg.create_thread( boost::bind( &eod_datafeed_spitter::process_task_list_, this ) );

			while ( !datafeed_.empty() )
			{
				const long processing_date = datafeed_.begin()->first;
				tasks_to_process_ = datafeed_.count( processing_date );
				sorted_datafeed::const_iterator start = datafeed_.lower_bound( processing_date );
				sorted_datafeed::const_iterator end = datafeed_.upper_bound( processing_date );

				if ( start != end )
				{
					const common::on_bar last_day_bar = start->second->create_on_bar();
					on_period_bar_ = start->second->create_on_period();

					for ( sorted_datafeed::const_iterator i = start ; i != end ; ++i )
						processing_bar_tasks_.push( new sorted_datafeed::const_iterator( i ) );
					wait_calculating_threads_();

					datafeed_.erase( processing_date );
					add_next_day_();

					manager_.on_bar( last_day_bar );
				}
				else
					datafeed_.erase( processing_date );
			}
			
			processing_bar_tasks_.stop();
			manager_.on_period( on_period_bar_ );

			tg.join_all();
		}
		//
		void eod_datafeed_spitter::add_next_day_()
		{
			for ( stock_data_list::const_iterator i = elements_to_delete_insert_.begin(), end = elements_to_delete_insert_.end() ; i != end ; ++i )
				if ( !(*i)->finished() )
					datafeed_.insert( std::make_pair( (*i)->current_day(), *i ) );
			elements_to_delete_insert_.clear();
		}
		void eod_datafeed_spitter::wait_calculating_threads_()
		{
			boost::mutex::scoped_lock lock( protect_elements_to_delete_insert_ );
			while ( tasks_to_process_ )
				tasks_solved_.wait( lock );
		}
		void eod_datafeed_spitter::process_task_list_()
		{
			while ( true )
			{
				boost::shared_ptr< sorted_datafeed::const_iterator > ci( processing_bar_tasks_.wait_pop() );
				if ( !ci )
					break;
				sorted_datafeed::const_iterator& i = *ci;
				manager_.on_stock( i->second->stock_name, i->second->create_on_stock_bar() );
				i->second->increment();
				{
					boost::mutex::scoped_lock lock( protect_elements_to_delete_insert_ );
					elements_to_delete_insert_.push_back( i->second );
					--tasks_to_process_;
					if ( tasks_to_process_ == 0)
						tasks_solved_.notify_one();
				}
			}
			
		}
	}
}

