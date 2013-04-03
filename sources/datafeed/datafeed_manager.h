#ifndef _STSC_DATAFEED_DATAFEED_MANAGER_H_
#define _STSC_DATAFEED_DATAFEED_MANAGER_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include <shared_name_storage.h>

#include <binary/format.h>

namespace stsc
{
	namespace datafeed
	{

		namespace details
		{
			struct stock_data
			{
				typedef system_utilities::common::shared_name_storage::shared_string shared_string;
				typedef boost::shared_ptr< binary::period > datafeed_period;

				shared_string stock_name;
				datafeed_period datafeed;
				binary::period::bars_type::const_iterator ci;
				//
				explicit stock_data( const shared_string& stock_name );
				//
				void set_datafeed( datafeed_period& dp );
				const bool finished() const;
				const long stock_data::current_day() const;
			};
			typedef boost::shared_ptr< details::stock_data > stock_data_ptr;
		}

		class datafeed_manager : protected virtual boost::noncopyable
		{
		protected:
			typedef system_utilities::common::shared_name_storage::shared_string shared_string;
		private:

			friend class eod_datafeed_storage;
			friend class eod_datafeed_spitter;
		public:
			explicit datafeed_manager();
			virtual ~datafeed_manager();
		private:
			virtual void new_bar_on_stock( const shared_string& stock_name, const common::price_bar& bar );
			virtual void new_bar_on_bar( const common::bar_type& bar );
			virtual void new_bar_on_period( const common::bar_type& bar );
			virtual void file_reading_error( const std::string& file_path );
		};
	}
}

#endif // _STSC_DATAFEED_DATAFEED_MANAGER_H_
