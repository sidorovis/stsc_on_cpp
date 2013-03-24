#ifndef _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_H_
#define _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_H_

#include <deque>
#include <set>
#include <stdexcept>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			class moving_median_tests;
		}
	}
	namespace engine
	{
		template< class T >
		class moving_median
		{
			friend class stsc::tests_::engine::moving_median_tests;

		public:
			typedef T value_type;
			typedef std::multiset< value_type > median_set;
			typedef std::deque< value_type > real_values;
			median_set lower_median_set_;
			median_set bigger_median_set_;
			real_values real_values_;
			const size_t window_;

		public:
			explicit moving_median( const size_t window )
				: window_( window % 2 ? window : window + 1 )
			{
				if ( window_ < 3 )
					throw std::invalid_argument( "moving median window should be bigger than 3" );
			}

		public:
			const bool mature() const
			{
				return real_values_.size() == window_;
			}
			void add_element( const value_type& key )
			{
				new_element( key );

				if ( real_values_.size() > window_ )
					pop_element();

				normalize_sets();
			}
			const value_type get_median()
			{
				if ( real_values_.size() >= window_ )
					return get_last_element( lower_median_set_ );
				else
				{
					if ( real_values_.empty() )
						throw std::logic_error( "there is no values in ts_median" );
					return real_values_.back();
				}
			}

		private:
			const value_type pop_first_element( median_set& mset )
			{
				const value_type result = *( mset.begin() );
				mset.erase( mset.begin() );
				return result;
			}
			const value_type pop_last_element( median_set& mset ) 
			{
				typename median_set::iterator i;// = --(mset.end());
				const value_type result = *i;
				mset.erase( i );
				return result;
			}
			const value_type get_last_element( const median_set &mset )
			{					
				return *( mset.rbegin() );
			}
			void pop_element()
			{
				const value_type poped_element = real_values_.front();
				real_values_.pop_front();
				if ( poped_element <= get_last_element( lower_median_set_ ) )
					lower_median_set_.erase( lower_median_set_.find( poped_element ) );
				else 
					bigger_median_set_.erase( bigger_median_set_.find( poped_element ) );
			}
			void new_element( const value_type& key )
			{
				if ( lower_median_set_.size() == ( window_ + 1 ) / 2 && get_last_element( lower_median_set_ )  <= key )
					bigger_median_set_.insert( key );
				else 
					lower_median_set_.insert( key );

				real_values_.push_back( key );					
			}
			void normalize_sets()
			{
				while ( lower_median_set_.size() > ( window_ + 1 ) / 2 )
					bigger_median_set_.insert( pop_last_element( lower_median_set_ ));
				while ( bigger_median_set_.size() > window_ / 2)
					lower_median_set_.insert( pop_first_element( bigger_median_set_ ));
			}
		};
	}	
}

#endif // _STSC_ENGINE_ALGORITHMS_MOVING_MEDIAN_H_
