#ifndef _STSC_DATAFEED_CSV_YAHOO_READER_TO_BINARY_PROCESSOR_H_
#define _STSC_DATAFEED_CSV_YAHOO_READER_TO_BINARY_PROCESSOR_H_

#include <string>
#include <map>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <stock_datafeed_processor.h>
#include <binary/format.h>

namespace stsc
{
	namespace datafeed
	{
		namespace csv
		{
			class yahoo_finance_to_binary_data : public datafeed::stock_datafeed_processor
			{
				typedef boost::shared_ptr< std::string > stock_name_ptr;

				mutable boost::mutex protect_datafeed_;
				typedef std::map< stock_name_ptr, stsc::datafeed::binary::period > datafeed_map;
				mutable datafeed_map datafeed_;
			public:
				explicit yahoo_finance_to_binary_data();
				~yahoo_finance_to_binary_data();
				void process_bar( const stock_name_ptr& stock_name, const common::price_bar& new_bar );
				void error_process( const std::string& reason, const std::string& file_path );
			private:
				datafeed::binary::period& period( const stock_name_ptr& stock_name );
			public:
				void save_to( const boost::filesystem::path& output_folder ) const;
			};
		}
	}
}


#endif // _STSC_DATAFEED_CSV_YAHOO_READER_TO_BINARY_PROCESSOR_H_

