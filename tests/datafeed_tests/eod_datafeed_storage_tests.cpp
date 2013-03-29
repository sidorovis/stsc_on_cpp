#include <test_registrator.h>

#include <time_tracker.h>

#include <eod_datafeed_storage.h>


using namespace stsc::datafeed;

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			void eod_datafeed_storage_constructor_tests()
			{
				datafeed_storage_manager m;
				BOOST_CHECK_THROW( eod_datafeed_storage( m, "", 0, 0 ), std::exception );
				BOOST_CHECK_THROW( eod_datafeed_storage( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 0 ), std::exception );
				BOOST_CHECK_NO_THROW( eod_datafeed_storage( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 1 ) );
			}
			void eod_datafeed_storage_read_datafeed_tests()
			{
				datafeed_storage_manager m;
				eod_datafeed_storage eds( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 1 );
				BOOST_CHECK_THROW( eds.add_stock_to_parse( "aapl" ), std::exception );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "a" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "amh" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "brkr" ) );
				BOOST_CHECK_THROW( eds.add_stock_to_parse( "amh" ), std::exception );
				BOOST_CHECK_NO_THROW( eds.read_datafeed() );
			}
			void eod_datafeed_storage_multithread_read_datafeed_tests()
			{
				datafeed_storage_manager m;
				eod_datafeed_storage eds( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 1 );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "a" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "amh" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "brkr" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "fve" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "idai" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "ksbi" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "muv" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "sior" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "tpam" ) );
				BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( "xynh" ) );
				BOOST_CHECK_NO_THROW( eds.multithread_read_datafeed() );
			}
			void eod_datafeed_storage_read_performance_tests()
			{
				using namespace boost::filesystem;

				static const std::string binary_datafeed_folder = SOURCE_DIR "/data/binary_yahoo_datafeed";
				if ( !exists( binary_datafeed_folder ) )
					return;
				datafeed_storage_manager m;
				eod_datafeed_storage eds( m, binary_datafeed_folder, 0, 0 );
				for( directory_iterator i( binary_datafeed_folder ), end ; i != end ; ++i  )
					BOOST_CHECK_NO_THROW( eds.add_stock_to_parse( i->path().filename() ) );
				BOOST_CHECK_NO_THROW( eds.multithread_read_datafeed() );
			}
		}
	}
}
