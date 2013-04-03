#include <test_registrator.h>

#include <time_tracker.h>

#include <time_helper.h>
#include <eod_datafeed_storage.h>

using namespace stsc::datafeed;

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			namespace
			{
				void eod_datafeed_storage_multithread_read_datafeed_performance_tests_helper( const size_t thread_amount )
				{
					using namespace boost::filesystem;

					datafeed_manager m;
					const long from = common::create_eod_time( 2008, 01, 01 );
					const long to = common::create_eod_time( 2008, 12, 31 );

					static const std::string binary_datafeed_folder = SOURCE_DIR "/data/binary_yahoo_datafeed";
					if ( !exists( binary_datafeed_folder ) )
						return;

					eod_datafeed_storage storage( m, SOURCE_DIR "/data/binary_yahoo_datafeed", from, to );
					size_t u = 0;
					for( directory_iterator i( binary_datafeed_folder ), end ; i != end && u < 150 ; ++i, ++u  )
						BOOST_CHECK_NO_THROW( storage.add_stock_to_parse( i->path().filename() ) );
					storage.multithread_read_datafeed();
				}
			}
			void eod_datafeed_storage_constructor_tests()
			{
				datafeed_manager m;
				BOOST_CHECK_THROW( eod_datafeed_storage( m, "", 0, 0 ), std::exception );
				BOOST_CHECK_THROW( eod_datafeed_storage( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 0 ), std::exception );
				BOOST_CHECK_NO_THROW( eod_datafeed_storage( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 1 ) );
			}
			void eod_datafeed_storage_read_datafeed_tests()
			{
				datafeed_manager m;
				const long from = common::create_eod_time( 2008, 01, 01 );
				const long to = common::create_eod_time( 2008, 12, 31 );
				eod_datafeed_storage eds( m, SOURCE_DIR "/tests/data/binary_data_example/", from, to );
				BOOST_CHECK_THROW( eds.add_stock_to_parse( "aapl" ), std::exception );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "a" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "amh" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "brkr" ) );
				BOOST_CHECK_THROW( eds.add_stock_to_parse( "amh" ), std::exception );
				BOOST_CHECK_NO_THROW( eds.read_datafeed() );
				BOOST_CHECK_EQUAL( eds.datafeed_.size(), 3ul );
				BOOST_CHECK_EQUAL( eds.datafeed_.begin()->first, from );
				BOOST_CHECK_EQUAL( (++eds.datafeed_.begin())->first, from + 1 );
				BOOST_CHECK_EQUAL( (++(++eds.datafeed_.begin()))->first, from + 1 );
			}
			void eod_datafeed_storage_multithread_read_datafeed_tests()
			{
				for ( size_t i = 1 ; i < 10 ; ++i )
					eod_datafeed_storage_multithread_read_datafeed_performance_tests_helper( i );
			}
			void eod_datafeed_storage_read_performance_tests()
			{
				using namespace boost::filesystem;

				static const std::string binary_datafeed_folder = SOURCE_DIR "/data/binary_yahoo_datafeed";
				if ( !exists( binary_datafeed_folder ) )
					return;
				datafeed_manager m;
				eod_datafeed_storage eds( m, binary_datafeed_folder, 0, 60000 );
				for( directory_iterator i( binary_datafeed_folder ), end ; i != end ; ++i  )
					BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( i->path().filename() ) );
				BOOST_CHECK_NO_THROW( eds.multithread_read_datafeed() );
			}
		}
	}
}
