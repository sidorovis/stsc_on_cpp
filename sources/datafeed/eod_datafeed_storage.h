#ifndef _STSC_EOD_DATAFEED_STORAGE_H_
#define _STSC_EOD_DATAFEED_STORAGE_H_

#include <string>
#include <set>
#include <map>
#include <ostream>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <ts_queue.h>

#include <common/types.h>

#include <binary/format.h>

#include <stock_datafeed.h>

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			void eod_datafeed_storage_read_datafeed_tests();
		}
	}

	namespace datafeed
	{
		class eod_datafeed_storage;
		class eod_datafeed_spitter;

		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );

		class eod_datafeed_storage_manager : virtual protected boost::noncopyable
		{
		public:
			eod_datafeed_storage_manager();
			virtual ~eod_datafeed_storage_manager();
			virtual const common::shared_name_storage& stock_names() = 0;
			//
			virtual void file_reading_error( const std::string& file_path );
		};

		/// end of day datafeed storage read (multithread/non multi thread) datafeed
		class eod_datafeed_storage : virtual protected boost::noncopyable
		{
			friend class eod_datafeed_spitter;
			friend void stsc::tests_::datafeed::eod_datafeed_storage_read_datafeed_tests();
			friend std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );
			//
			eod_datafeed_storage_manager& manager_;
			
			const boost::filesystem::path datafeed_file_path_;
			const long period_from_;
			const long period_to_;

			typedef system_utilities::common::ts_queue< const common::shared_string > stock_names_queue;
			stock_names_queue stock_names_queue_;

			boost::mutex protect_datafeed_;
			typedef std::multimap< long, stock_datafeed_ptr > sorted_datafeed;
			sorted_datafeed datafeed_;

		public:
			explicit eod_datafeed_storage( eod_datafeed_storage_manager& manager, const std::string& datafeed_file_path, const long from, const long to );
			~eod_datafeed_storage();
			//
			void preprocess_stock( const common::shared_string& stock_name );
			//
			void read_datafeed();
			void multithread_read_datafeed( const size_t thread_amount = 4ul );
		private:
			void read_datafeed_from_file_storage_();
			void read_period_( const boost::filesystem::path& from, binary::period& to );
		};

		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );
	}
}

#endif // _STSC_EOD_DATAFEED_STORAGE_H_
