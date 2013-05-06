#ifndef _STSC_DATAFEED_CSV_YAHOO_FINANCE_READER_H_
#define _STSC_DATAFEED_CSV_YAHOO_FINANCE_READER_H_

#include <string>
#include <list>
#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

#include <common/bar_types.h>

#include <stock_datafeed_processor.h>

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			namespace csv
			{
				void yahoo_finance_reader_unit_tests();
			}
		}
	}
	namespace datafeed
	{
		namespace csv
		{
			namespace details
			{
				struct yahoo_finance_file
				{
					std::string file_name;
					std::string file_path;
					explicit yahoo_finance_file( const std::string&, const std::string& );
				};
				typedef boost::shared_ptr< yahoo_finance_file > yahoo_finance_file_ptr;

			}

			class yahoo_finance_reader : virtual protected boost::noncopyable
			{
				friend void stsc::tests_::datafeed::csv::yahoo_finance_reader_unit_tests();

				stock_datafeed_processor& datafeed_processor_;

				boost::mutex file_vector_mutex_;
				std::list< details::yahoo_finance_file_ptr > datafeed_files_;

				const bool protected_scan_;

			public:
				explicit yahoo_finance_reader( stock_datafeed_processor& dp, const std::string& datafeed_folder, const bool protected_scan = true );
				~yahoo_finance_reader();
				//
				void process( const size_t thread_size = 1ul );
			private:
				static bool file_is_datafeed_file_( const std::string& file_name );
				void processing_thread_();

				const details::yahoo_finance_file_ptr file_path_to_process_();

				static const bool first_line_is_correct_( std::ifstream& file );
				void process_datafeed_( std::ifstream& file, const std::string& file_name );
				const std::string create_stock_name_( const std::string& file_name );
			};
		}
	}
}

#endif // _STSC_DATAFEED_CSV_YAHOO_FINANCE_READER_H_