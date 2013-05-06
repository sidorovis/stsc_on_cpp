#ifndef _STSC_ENGINE_SERIES_STORAGE_SERIE_H_
#define _STSC_ENGINE_SERIES_STORAGE_SERIE_H_

#include <typeinfo> 
#include <sstream>

#include <boost/shared_ptr.hpp>

#include <common/types.h>

namespace stsc
{
	namespace engine
	{
		namespace series_storage
		{
			class serie_prototype
			{
			protected:
				virtual ~serie_prototype();
			public:
				virtual void container_check( const std::type_info& ti ) const = 0;
			};
			//
			template< typename signal_type >
			class serie : public serie_prototype
			{
			public:
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef boost::shared_ptr< const signal_type > signal_type_const_ptr;
				//
				virtual ~serie(){}
				//
				virtual void container_check( const std::type_info& ti ) const = 0;
				//
				virtual void clear() = 0;
				virtual void insert( const common::index& key, const signal_type_ptr& signal_ptr ) = 0;
				virtual void insert( const common::index& key, signal_type* const signal_ptr ) = 0;
				virtual void insert( const common::index& key, const signal_type& signal_ptr ) = 0;
				//
				virtual const signal_type& at( const common::index& key ) const = 0;
				virtual const signal_type_const_ptr ptr_at( const common::index& key ) const = 0;
				virtual const size_t size() const = 0;
				virtual const bool empty() const = 0;
			};


			//
			template< typename signal_type >
			class serie_ptr : public boost::shared_ptr< serie< signal_type > >
			{
			public:
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef boost::shared_ptr< const signal_type > signal_type_const_ptr;

				explicit serie_ptr()
				{
				}
				serie_ptr( serie< signal_type >* pointer )
					: boost::shared_ptr< serie< signal_type > >( pointer )
				{
				}
			};

			template< typename signal_type >
			class const_serie_ptr : public boost::shared_ptr< const serie< signal_type > >
			{
			public:
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef boost::shared_ptr< const signal_type > signal_type_const_ptr;

				explicit const_serie_ptr()
				{
				}
				const_serie_ptr( const serie< signal_type >* pointer )
					: boost::shared_ptr< const serie< signal_type > >( pointer )
				{
				}
				const_serie_ptr( const serie_ptr< signal_type >& pointer )
					: boost::shared_ptr< const serie< signal_type > >( pointer )
				{
				}
			};
		}
	}
}

#endif // _STSC_ENGINE_SERIES_STORAGE_SERIE_H_
