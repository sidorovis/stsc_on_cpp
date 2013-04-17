#ifndef _STSC_ENGINE_SERIES_STORAGE_SERIE_SUBSCRIPTION_H_
#define _STSC_ENGINE_SERIES_STORAGE_SERIE_SUBSCRIPTION_H_

#include <series_storage/serie.h>

namespace stsc
{
	namespace engine
	{
		namespace series_storage
		{
			template< typename signal_type >
			class serie_subscription
			{
				typedef serie< signal_type > serie_type;
				const serie_type& serie_;

				typedef boost::shared_ptr< signal_type > signal_type_ptr;
				typedef boost::shared_ptr< const signal_type > signal_type_const_ptr;
			public:
				explicit serie_subscription( const serie_type& serie )
					: serie_( serie )
				{
				}
				~serie_subscription()
				{
				}
				//
				void subscription_check( const std::type_info& ti ) const
				{
					return serie_.subscription_check( ti );
				}
				void container_check( const std::type_info& ti ) const
				{
					return serie_.container_check( ti );
				}
				//
				const signal_type& at( const common::index& key ) const
				{
					return serie_.at( key );
				}
				const signal_type_const_ptr ptr_at( const common::index& key ) const
				{
					return serie_.ptr_at( key );
				}
				const size_t size() const
				{
					return serie_.size();
				}
				const bool empty() const
				{
					return serie_.empty();
				}
			};
			//
			template< typename signal_type >
			serie_subscription< signal_type > make_subscription( const serie< signal_type >& s )
			{
				return serie_subscription< signal_type >( s );
			}
		}
	}
}

#endif // _STSC_ENGINE_SERIES_STORAGE_SERIE_SUBSCRIPTION_H_
