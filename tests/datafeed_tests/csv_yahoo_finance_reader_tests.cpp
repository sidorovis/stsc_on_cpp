#include <test_registrator.h>

#include <csv/yahoo_finance_reader.h>

#include <boost/filesystem.hpp>

#include <time_tracker.h>

using namespace stsc::datafeed::csv;

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			namespace csv
			{
				namespace
				{
					class datafeed_processor : public stsc::datafeed::stock_datafeed_processor
					{
						typedef boost::shared_ptr< std::string > stock_name_ptr;
						typedef std::vector< common::price_bar > bars;
					public:
						std::map< std::string, bars > datafeed_;
					private:

						boost::mutex protect_map_;

					public:
						explicit datafeed_processor(){}
						virtual ~datafeed_processor(){}
						virtual void process_bar( const stock_name_ptr& stock_name, const common::price_bar& new_bar )
						{
							boost::mutex::scoped_lock lock( protect_map_ );
							datafeed_[ *stock_name ].push_back( new_bar );
						}
						virtual void error_process( const std::string& reason, const std::string& file_path )
						{
						}
					};
					size_t yahoo_finance_reader_multithread_test_helper( const size_t thread_size )
					{
						system_utilities::common::time_tracker tt;
						datafeed_processor dp;
						yahoo_finance_reader yfr( dp, SOURCE_DIR "/tests/data/yahoo_finance_to_binary_data", true );
						yfr.process( thread_size );
						return tt.milliseconds();						
					}
				}

				void yahoo_finance_reader_constructor_tests()
				{
					using namespace boost::filesystem;

					datafeed_processor dp;
					BOOST_CHECK_THROW( yahoo_finance_reader( dp, SOURCE_DIR "/unknown/please/be/unexisted/folder" ), std::exception );
					BOOST_CHECK_THROW( yahoo_finance_reader( dp, SOURCE_DIR "/CMakeLists.txt" ), std::exception );
				}
				void yahoo_finance_reader_unit_tests()
				{
					BOOST_CHECK_EQUAL( yahoo_finance_reader::file_is_datafeed_file_( "HELLO.csv" ), true );
					BOOST_CHECK_EQUAL( yahoo_finance_reader::file_is_datafeed_file_( "HELLOcsv" ), false );
					BOOST_CHECK_EQUAL( yahoo_finance_reader::file_is_datafeed_file_( "HELLOWORLD.csv" ), false );
					BOOST_CHECK_EQUAL( yahoo_finance_reader::file_is_datafeed_file_( ".csv" ), false );
					BOOST_CHECK_EQUAL( yahoo_finance_reader::file_is_datafeed_file_( "A.csv" ), true );
					BOOST_CHECK_EQUAL( yahoo_finance_reader::file_is_datafeed_file_( "1.csv" ), false );
					BOOST_CHECK_EQUAL( yahoo_finance_reader::file_is_datafeed_file_( "A1.csv" ), false );

					datafeed_processor dp;
					yahoo_finance_reader yfr( dp, SOURCE_DIR "/tests/data/yahoo_finance_to_binary_data", true );
					BOOST_CHECK_EQUAL( yfr.datafeed_files_.size(), 4ul );
					yfr.datafeed_files_.pop_back();
					yfr.datafeed_files_.pop_back();
					BOOST_CHECK_NO_THROW( yfr.process( 2ul ) );
					BOOST_CHECK_EQUAL( dp.datafeed_.size(), 2ul );
					BOOST_CHECK_EQUAL( dp.datafeed_[ "aapl" ].size(), 7188ul );
					BOOST_CHECK_EQUAL( dp.datafeed_[ "epam" ].size(), 272ul );
				}
				//
				void yahoo_finance_reader_performance_tests()
				{
					const size_t by_thread_1 = yahoo_finance_reader_multithread_test_helper( 1 );
					const size_t by_thread_2 = yahoo_finance_reader_multithread_test_helper( 2 );
					const size_t by_thread_3 = yahoo_finance_reader_multithread_test_helper( 3 );
					BOOST_CHECK_EQUAL( by_thread_3 <= by_thread_1, true );
					BOOST_CHECK_EQUAL( by_thread_2 <= by_thread_1, true );
					for ( size_t i = 4 ; i < 15 ; ++i )
						BOOST_CHECK_NO_THROW( yahoo_finance_reader_multithread_test_helper( i ) );
				}
			}
		}
	}
}
