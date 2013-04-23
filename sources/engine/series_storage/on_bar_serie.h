#ifndef _STSC_ENGINE_SERIES_STORAGE_ON_BAR_SERIE_H_
#define _STSC_ENGINE_SERIES_STORAGE_ON_BAR_SERIE_H_

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
				struct on_bar_serie
				{
					typedef typename series_storage::serie< signal_type > typed_serie;
					typedef boost::shared_ptr< typed_serie > serie_ptr;

					serie_ptr serie_;
				};
			}
		}
	}
}


#endif // _STSC_ENGINE_SERIES_STORAGE_ON_BAR_SERIE_H_

