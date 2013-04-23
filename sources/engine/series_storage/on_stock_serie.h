#ifndef _STSC_ENGINE_SERIES_STORAGE_ON_STOCK_SERIE_H_
#define _STSC_ENGINE_SERIES_STORAGE_ON_STOCK_SERIE_H_

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include <series_storage/serie.h>

namespace stsc
{
	namespace engine
	{
		namespace series_storage
		{
			namespace details
			{
				template< typename signal_type >
				struct on_stock_serie
				{
					typedef typename series_storage::serie< signal_type > typed_serie;
					typedef boost::shared_ptr< typed_serie > serie_ptr;

					typedef std::map< common::shared_string, serie_ptr > series;
					series series_;
				};
			}
		}
	}
}


#endif // _STSC_ENGINE_SERIES_STORAGE_ON_STOCK_SERIE_H_

