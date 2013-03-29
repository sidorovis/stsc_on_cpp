#ifndef _STSC_EOD_DATAFEED_STORAGE_H_
#define _STSC_EOD_DATAFEED_STORAGE_H_

#include <string>
#include <set>
#include <ostream>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <multikey_tree.h>
#include <ts_queue.h>

#include <binary/format.h>

namespace stsc
{
	namespace datafeed
	{
		class eod_datafeed_storage;

		class datafeed_storage_manager
		{
			friend class eod_datafeed_storage;
		public:
			virtual ~datafeed_storage_manager(){}
		private:
			virtual void new_bar_on_stock( const std::string& stock_name, const common::price_bar& bar )
			{
			}
			virtual void new_bar_on_bar( const std::string& stock_name, const common::bar_type& bar )
			{
			}
			virtual void new_bar_on_period( const std::string& stock_name, const common::bar_type& bar )
			{
			}
			virtual void file_reading_error( const std::string& file_path )
			{
			}
		};

		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );

		namespace details
		{
			struct stock_data
			{
				std::string stock_name;
				binary::period data;
				long from;
				long to;
			};
		}

		/// end of day datafeed storage read (multithread/non multi thread) datafeed
		/// process periods calling method

		class eod_datafeed_storage : protected boost::noncopyable
		{
			friend std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );
			datafeed_storage_manager& manager_;
			
			const boost::filesystem::path datafeed_file_path_;
			const long from_;
			const long to_;
			
			typedef std::set< std::string > stock_names_set;
			stock_names_set names_to_parse_;

			system_utilities::common::ts_queue< std::string > files_to_parse_;


			system_utilities::common::multikey_tree< binary::period > market_data_;

		public:
			explicit eod_datafeed_storage( datafeed_storage_manager& manager, const std::string& datafeed_file_path, const long from, const long to );
			~eod_datafeed_storage();
			//
			void add_stock_to_parse( const std::string& stock_name );
			void read_datafeed();
			void multithread_read_datafeed( const size_t thread_amount = 4ul );
		private:
			void read_datafeed_from_file_storage_();
			void read_period_( const boost::filesystem::path& from, binary::period& to );
		public:
			void process_period( const size_t thread_amount = 4ul );
		};

		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );
	}
}

#endif // _STSC_EOD_DATAFEED_STORAGE_H_
