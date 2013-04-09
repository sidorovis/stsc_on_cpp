#ifndef _STSC_ENGINE_SIGNAL_STORAGES_SERIE_H_
#define _STSC_ENGINE_SIGNAL_STORAGES_SERIE_H_

#include <typeinfo> 

#include <boost/shared_ptr.hpp>

#include <bar_types.h>

namespace stsc
{
	namespace engine
	{
		class series_storage;

		namespace signal_storages
		{
			template< typename signal_type >
			class serie
			{
				friend class series_storage;
			public:
				typedef boost::shared_ptr< signal_type > signal_type_ptr;
			protected:
				virtual ~serie(){}
			private:
				static const std::type_info& signal_type_info_;
			public:
				void subscription_check( const std::type_info& ti ) const
				{
					std::stringstream error_line;
					error_line << "serie signal type with " << signal_type_info_.name() << " decline subscription on " << ti.name();
					if ( ti != signal_type_info_ )
						throw std::logic_error( error_line.str() );
				}
				virtual void container_check( const std::type_info& ti ) const = 0;
			public:
				virtual void clear() = 0;
				virtual void insert( const common::index& key, const signal_type_ptr& signal_ptr ) = 0;
				virtual void insert( const common::index& key, signal_type* const signal_ptr ) = 0;
				virtual void insert( const common::index& key, const signal_type& signal_ptr ) = 0;
				//
				virtual const signal_type& at( const common::index& key ) const = 0;
				virtual const signal_type_ptr ptr_at( const common::index& key ) const = 0;
				virtual const size_t size() const = 0;
				virtual const bool empty() const = 0;
			};

			template< typename signal_type >
			const std::type_info& serie< signal_type >::signal_type_info_ = typeid( signal_type );
		}
	}
}

#endif // _STSC_ENGINE_SIGNAL_STORAGES_SERIE_H_
