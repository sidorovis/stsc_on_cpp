#ifndef _STSC_ENGINE_SERIES_STORAGE_VECTOR_SERIE_H_
#define _STSC_ENGINE_SERIES_STORAGE_VECTOR_SERIE_H_

#include <vector>

#include <series_storage/serie.h>

namespace stsc
{
	namespace engine
	{
		namespace series_storage
		{

			template< typename signal_type, size_t default_increment = 2, size_t default_size = 56 >
			class vector_serie : public serie< signal_type >
			{
			private:
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef std::vector< signal_type_ptr > signals_vector;
				typedef boost::shared_ptr< signals_vector > signals_vector_ptr;

				static const std::type_info& container_type_info_;
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
				signals_vector_ptr signals_vector_;
			public:
				explicit vector_serie()
					: signals_vector_( new signals_vector() )
				{
					signals_vector_->reserve( default_size );
				}
				virtual ~vector_serie()
				{
				}
				//
				virtual void container_check( const std::type_info& ti ) const
				{
					if ( ti != container_type_info_ )
						throw std::logic_error( std::string("serie container type with ") + container_type_info_.name() + " decline subscription on " + ti.name() );
				}
			public:
				void clear()
				{
					signals_vector_->clear();
				}
				//
				void insert( const common::index& key, const signal_type_ptr& signal_ptr )
				{
					if ( signals_vector_->capacity() <= key )
						signals_vector_->reserve( (key + 1) * default_increment );
					if ( signals_vector_->size() <= key )
						signals_vector_->resize( key + 1 );
					(*signals_vector_)[ key ] = signal_ptr;
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
					if ( signals_vector_->size() <= key || (*signals_vector_)[ key ] == NULL )
						throw std::logic_error( "element not exist at vector_serie" );
					else
						return *( (*signals_vector_)[ key ] );
				}
				const signal_type_const_ptr ptr_at( const common::index& key ) const
				{
					if ( signals_vector_->size() <= key )
						return signal_type_const_ptr();
					else
						return (*signals_vector_)[ key ];
				}
				const size_t size() const
				{
					return signals_vector_->size();
				}
				const bool empty() const
				{
					return signals_vector_->empty();
				}

			};
			template< typename signal_type, size_t default_increment, size_t default_size >
			const std::type_info& vector_serie< signal_type, default_increment, default_size >::container_type_info_ = 
				typeid( vector_serie< signal_type, default_increment, default_size >::signals_vector );
			//
			template< typename signal_type >
			serie_ptr< signal_type > create_vector_serie_ptr()
			{
				return serie_ptr< signal_type >( new vector_serie< signal_type >() );
			}
		}
	}
}

#endif // _STSC_ENGINE_SERIES_STORAGE_VECTOR_SERIE_H_

