#ifndef _STSC_ENGINE_SIGNAL_STORAGES_MAP_SERIE_H_
#define _STSC_ENGINE_SIGNAL_STORAGES_MAP_SERIE_H_

#include <map>

#include <boost/noncopyable.hpp>

#include <bar_types.h>

#include <signal_storages/serie_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace signal_storages
		{
			template< typename signal_type >
			class map_serie : serie_prototype< signal_type >
			{
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef boost::shared_ptr< signal_type const > signal_type_const_ptr;
				typedef std::map< const common::index, signal_type_ptr > signals_map;
			public:
				typedef typename signals_map::value_compare value_compare;
				typedef typename signals_map::allocator_type allocator_type;
				typedef typename signals_map::size_type size_type;
				typedef typename signals_map::difference_type difference_type;
				typedef typename signals_map::pointer pointer;
				typedef typename signals_map::const_pointer const_pointer;
				typedef typename signals_map::reference reference;
				typedef typename signals_map::const_reference const_reference;
				typedef typename signals_map::iterator iterator;
				typedef typename signals_map::const_iterator const_iterator;
				typedef typename signals_map::reverse_iterator reverse_iterator;
				typedef typename signals_map::const_reverse_iterator const_reverse_iterator;
				typedef typename signals_map::value_type value_type;
			private:
				signals_map signals_map_;
			public:
				explicit map_serie()
				{
				}
				~map_serie()
				{
				}
				//
				void clear()
				{
					signals_map_.clear();
				}
				//
				void insert( const common::index& key, const signal_type_ptr& signal_ptr )
				{
					const bool inserted = signals_map_.insert( std::make_pair( key, signal_ptr ) ).second;
					if ( !inserted )
						throw std::logic_error( "map_serie can't insert element (possible it already stored)" );
				}
				void insert( const common::index& key, signal_type* const signal_ptr )
				{
					return insert( key, signal_type_ptr( signal_ptr ) );
				}
				//
				const signal_type& at( const common::index& key ) const
				{
					const_iterator ci = signals_map_.find( key );
					if ( ci != signals_map_.end() )
						return *(ci->second);
					throw std::invalid_argument( "unexisted key for map_serie" );
				}
				const signal_type_ptr ptr_at( const common::index& key ) const
				{
					const_iterator ci = signals_map_.find( key );
					if ( ci != signals_map_.end() )
						return ci->second;
					throw std::invalid_argument( "unexisted key for map_serie" );
				}
				//
				iterator begin()
				{
					return signals_map_.begin();
				}
				iterator end()
				{
					return signals_map_.end();
				}
				const_iterator begin() const
				{
					return signals_map_.begin();
				}
				const_iterator end() const
				{
					return signals_map_.end();
				}
				//
				const size_t size() const
				{
					return signals_map_.size();
				}
				const bool empty() const
				{
					return signals_map_.empty();
				}
			};
		}
	}
}


#endif // _STSC_ENGINE_SIGNAL_STORAGES_MAP_SERIE_H_
