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
			struct on_stock_bar
			{
				typedef common::shared_string shared_string;

				const shared_string& stock_name;
				const common::price_bar& value;
				const size_t index;
				//
				explicit on_stock_bar( const shared_string& sn, const common::price_bar& b, const size_t i );
			};
			struct on_bar
			{
				const common::bar_type value;
				const size_t index;
				//
				explicit on_bar( const common::bar_type& b, const size_t i );
			};
			struct on_period
			{
				common::bar_type value;
				size_t index;
				//
				explicit on_period( const common::bar_type& b, const size_t i );
				explicit on_period();
			};
			//
			class stock_data
			{
			public:
				typedef system_utilities::common::shared_name_storage::shared_string shared_string;
				typedef boost::shared_ptr< binary::period > datafeed_period;
			private:
				shared_string stock_name;
				datafeed_period datafeed;
				binary::period::bars_type::const_iterator ci;
				size_t index;
				//
			public:
				explicit stock_data( const shared_string& stock_name );
				//
				void set_datafeed( datafeed_period& dp );
				//
				const bool finished() const;
				const long stock_data::current_day() const;
				//
				void increment();
				//
				on_stock_bar create_on_stock_bar() const;
				on_bar create_on_bar() const;
				on_period create_on_period() const;
			};
			typedef boost::shared_ptr< details::stock_data > stock_data_ptr;
		}

		class datafeed_manager : protected virtual boost::noncopyable
		{
		private:

			friend class eod_datafeed_storage;
			friend class eod_datafeed_spitter;
		public:
			explicit datafeed_manager();
			virtual ~datafeed_manager();
		private:
			virtual void new_bar_on_stock( const details::on_stock_bar& bar );
			virtual void new_bar_on_bar( const details::on_bar& bar );
			virtual void new_bar_on_period( const details::on_period& bar );
			//
			virtual void file_reading_error( const std::string& file_path );
		};
	}
}

#endif // _STSC_DATAFEED_DATAFEED_MANAGER_H_
