#ifndef _STSC_ENGINE_SERIES_STORAGE_MAP_SERIE_H_
#define _STSC_ENGINE_SERIES_STORAGE_MAP_SERIE_H_

#include <map>
#include <sstream>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <series_storage/serie.h>

namespace stsc
{
	namespace engine
	{
		namespace series_storage
		{
			template< typename signal_type >
			class map_serie : public serie< signal_type >
			{
			private:
				typedef serie< signal_type > serie_type;
				typedef std::map< const common::index, signal_type_ptr > signals_map;
				typedef boost::shared_ptr< signals_map > signal_map_ptr;

				static const std::type_info& container_type_info_;
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
				signal_map_ptr signals_map_;
			public:
				explicit map_serie()
					: signals_map_( new signals_map() )
				{
				}
				virtual ~map_serie()
				{
				}
				//
				virtual void container_check( const std::type_info& ti ) const
				{
					std::stringstream error_line;
					error_line << "serie signal type with " << container_type_info_.name() << " decline subscription on " << ti.name();
					if ( ti != container_type_info_ )
						throw std::logic_error( error_line.str() );
				}
			public:
				void clear()
				{
					signals_map_->clear();
				}
				//
				void insert( const common::index& key, const signal_type_ptr& signal_ptr )
				{
					const bool inserted = signals_map_->insert( std::make_pair( key, signal_ptr ) ).second;
					if ( !inserted )
						throw std::logic_error( "map_serie can't insert element (possible it already stored)" );
				}
				void insert( const common::index& key, signal_type* const signal_ptr )
				{
					return insert( key, signal_type_ptr( signal_ptr ) );
				}
				void insert( const common::index& key, const signal_type& signal_ptr )
				{
					return insert( key, signal_type_ptr( new signal_type( signal_ptr ) ) );
				}
				//
				const signal_type& at( const common::index& key ) const
				{
					const_iterator ci = signals_map_->find( key );
					if ( ci != signals_map_->end() )
						return *(ci->second);
					throw std::invalid_argument( "unexisted key for map_serie" );
				}
				const signal_type_const_ptr ptr_at( const common::index& key ) const
				{
					const_iterator ci = signals_map_->find( key );
					if ( ci != signals_map_->end() )
						return ci->second;
					return signal_type_ptr();
				}
				const size_t size() const
				{
					return signals_map_->size();
				}
				const bool empty() const
				{
					return signals_map_->empty();
				}
				//			
				iterator begin()
				{
					return signals_map_->begin();
				}
				iterator end()
				{
					return signals_map_->end();
				}
				const_iterator begin() const
				{
					return signals_map_->begin();
				}
				const_iterator end() const
				{
					return signals_map_->end();
				}
				//
			};
			//
			template< typename signal_type >
			const std::type_info& map_serie< signal_type >::container_type_info_ = typeid( map_serie< signal_type >::signals_map );
			//
			template< typename signal_type >
			serie_ptr< signal_type > create_map_serie_ptr()
			{
				return serie_ptr< signal_type >( new map_serie< signal_type >() );
			}
		}
	}
}


#endif // _STSC_ENGINE_SERIES_STORAGE_MAP_SERIE_H_
