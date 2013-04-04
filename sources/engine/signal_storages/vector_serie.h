#ifndef _STSC_ENGINE_SIGNAL_STORAGES_VECTOR_SERIE_H_
#define _STSC_ENGINE_SIGNAL_STORAGES_VECTOR_SERIE_H_

#include <vector>

#include <boost/shared_ptr.hpp>

#include <bar_types.h>

#include <signal_storages/serie_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace signal_storages
		{
			template< typename signal_type, signal_type default_value = signal_type(), size_t default_increment = 10, size_t default_size = 56 >
			class vector_serie : serie_prototype< signal_type >
			{
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef boost::shared_ptr< signal_type const > signal_type_const_ptr;
				typedef std::vector< signal_type_ptr > signals_vector;
			public:
				typedef typename signals_vector::allocator_type allocator_type;
				typedef typename signals_vector::size_type size_type;
				typedef typename signals_vector::difference_type difference_type;
				typedef typename signals_vector::pointer pointer;
				typedef typename signals_vector::const_pointer const_pointer;
				typedef typename signals_vector::reference reference;
				typedef typename signals_vector::const_reference const_reference;
				typedef typename signals_vector::iterator iterator;
				typedef typename signals_vector::const_iterator const_iterator;
				typedef typename signals_vector::reverse_iterator reverse_iterator;
				typedef typename signals_vector::const_reverse_iterator const_reverse_iterator;
				typedef typename signals_vector::value_type value_type;
			private:
				signals_vector signals_vector_;
			public:
				explicit vector_serie()
				{
					signals_vector_.reserve( default_size );
				}
				~vector_serie()
				{
				}
				//
				size_t size() const
				{
					return signals_vector_.size();
				}
				const bool empty() const
				{
					return signals_vector_.empty();
				}
				void clear()
				{
					signals_vector_.clear();
				}
				//
				void insert( const common::index& key, const signal_type_ptr& signal_ptr )
				{
					if ( signals_vector_.capacity() <= key )
						signals_vector_.reserve( key + 1 + default_increment );
					if ( signals_vector_.size() <= key )
						signals_vector_.resize( key + 1 );
					signals_vector_[ key ] = signal_ptr;
				}
				void insert( const common::index& key, signal_type* const signal_ptr )
				{
					return insert( key, signal_type_ptr( signal_ptr ) );
				}
				void insert( const common::index& key, const signal_type& signal_ptr )
				{
					return insert( key, signal_type_ptr( new signal_type( signal_ptr ) ) );
				}
				const signal_type& at( const common::index& key ) const
				{
					if ( signals_vector_.size() <= key || signals_vector_[ key ] == NULL )
						throw std::logic_error( "element not exist at vector_serie" );
					else
						return *( signals_vector_[ key ] );
				}
				const signal_type_ptr ptr_at( const common::index& key ) const
				{
					if ( signals_vector_.size() <= key )
						return signal_type_ptr();
					else
						return signals_vector_[ key ];
				}
			};
		}
	}
}

#endif // _STSC_ENGINE_SIGNAL_STORAGES_VECTOR_SERIE_H_

