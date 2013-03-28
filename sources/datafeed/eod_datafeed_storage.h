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
			virtual void file_reading_error( const std::string& file_path )
			{
			}
		};

		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );

		/// end of day datafeed storage read (multithread/non multi thread) datafeed
		/// 

		class eod_datafeed_storage : protected boost::noncopyable
		{
			friend std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );
			datafeed_storage_manager& manager_;
			
			const boost::filesystem::path datafeed_file_path_;
			
			typedef std::set< std::string > stock_names_set;
			stock_names_set names_to_parse_;

			system_utilities::common::ts_queue< std::string > files_to_parse_;

			system_utilities::common::multikey_tree< binary::period > market_data_;

		public:
			explicit eod_datafeed_storage( datafeed_storage_manager& manager, const std::string& datafeed_file_path );
			~eod_datafeed_storage();
			//
			void add_stock_to_parse( const std::string& stock_name );
			void read_datafeed();
			void multithread_read_datafeed( const size_t thread_amount = 4 );
		private:
			void read_datafeed_from_file_storage_();
			void read_period_( const boost::filesystem::path& from, binary::period& to );
		public:
			void process_period( const long from, const long to );
		};

		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds );
	}
}

#endif // _STSC_EOD_DATAFEED_STORAGE_H_
