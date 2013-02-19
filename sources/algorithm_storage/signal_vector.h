#ifndef _STSC_ALGORITHM_STORAGE_SIGNAL_VECTOR_H_
#define _STSC_ALGORITHM_STORAGE_SIGNAL_VECTOR_H_

#include <map>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <bar_types.h>

namespace stsc
{
	namespace algorithm_storage
	{
		template< typename signal_type >
		class algorithm_prototype;

		// signal_vector< type > template is a way to store signals from algorithms
		// notice that signal_vector< type > clear memory after signals by itself, please just send here pointers to your data
		// for example: 
		// signal_vector< double > sv;
		// sv.insert( common::bar_type(), new double( 1.5 ) );
		// Attention: !!! NEVER delete memory that you send to signal_vector it will terminate the application

		template< typename type >
		class signal_vector
		{
			friend class engine_storage;
			friend class algorithm_prototype< type >;
		public:
			typedef type signal_type;
			typedef const type* const pointer;
		private:
			typedef std::map< const common::bar_type* const, const signal_type* > signals_map;
			typedef boost::shared_ptr< signals_map > signal_map_ptr;
			signal_map_ptr signals_map_;
		protected:
			explicit signal_vector()
				: signals_map_( new signals_map() )
			{
			}
		private:
			void operator=( const signal_vector<type>& );
		public:
			signal_vector( const signal_vector< type >& copy )
				: signals_map_( copy.signals_map_ )
			{
			}
			~signal_vector()
			{
				clear();
			}
			void clear()
			{
				for( signals_map::iterator i = signals_map_->begin() ; i != signals_map_->end() ; ++i )
					delete i->second;
				signals_map_->clear();
			};
			void insert( const common::bar_type& bar, const signal_type* data )
			{
				if ( !(signals_map_->insert( std::make_pair( &bar, data ) ).second) )
					throw std::logic_error( "impossible to add to signal on single bar" );
			}
			const signal_type* at( const common::bar_type& bar ) const 
			{
				signals_map::const_iterator i = signals_map_->find( &bar );
				if ( i == signals_map_->end() )
					return NULL;
				return &(*(i->second));
			}
		};
	}
}

#endif // _STSC_ALGORITHM_STORAGE_SIGNAL_VECTOR_H_
