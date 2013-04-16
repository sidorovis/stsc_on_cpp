#ifndef _STSC_ENGINE_SERIES_STORAGE_H_
#define _STSC_ENGINE_SERIES_STORAGE_H_

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <bar_types.h>

#include <signal_storages/serie.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			typedef boost::shared_ptr< signal_storages::serie > serie_ptr;
			//
			struct stocks_storage : public std::map< common::shared_string, serie_ptr >
			{
			};
			struct on_stock_algorithm_series : public std::map< common::shared_string, stocks_storage >
			{
			};
			struct on_bar_algorithm_series : public std::map< common::shared_string, serie_ptr >
			{
			};
			struct on_period_algorithm_series : public std::map< common::shared_string, serie_ptr >
			{
			};
		}

		class series_storage : virtual protected boost::noncopyable
		{
			details::on_stock_algorithm_series on_stock_series_;
			details::on_bar_algorithm_series on_bar_series_;
			details::on_period_algorithm_series on_period_series_;

		public:
			explicit series_storage();
			~series_storage();
			//
		};
	}
}


#endif // _STSC_ENGINE_SERIES_STORAGE_H_

