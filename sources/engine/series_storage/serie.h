#ifndef _STSC_ENGINE_SERIES_STORAGE_SERIE_H_
#define _STSC_ENGINE_SERIES_STORAGE_SERIE_H_

#include <typeinfo> 
#include <sstream>

#include <boost/shared_ptr.hpp>

#include <bar_types.h>

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
				virtual void subscription_check( const std::type_info& ti ) const = 0;
				virtual void container_check( const std::type_info& ti ) const = 0;
			};

			template< typename signal_type >
			class serie : public serie_prototype
			{
			public:
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef boost::shared_ptr< const signal_type > signal_type_const_ptr;
			protected:
				virtual ~serie(){}
			private:
				static const std::type_info& signal_type_info_;
			public:
				virtual void subscription_check( const std::type_info& ti ) const;
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

			template< typename signal_type >
			const std::type_info& serie< signal_type >::signal_type_info_ = typeid( signal_type );

			template< typename signal_type >
			void serie< signal_type >::subscription_check( const std::type_info& ti ) const
			{
				std::stringstream error_line;
				error_line << "serie signal type with " << signal_type_info_.name() << " decline subscription on " << ti.name();
				if ( ti != signal_type_info_ )
					throw std::logic_error( error_line.str() );
			}

		}
	}
}

#endif // _STSC_ENGINE_SERIES_STORAGE_SERIE_H_
