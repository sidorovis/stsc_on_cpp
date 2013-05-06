#include <test_registrator.h>

#include <time_tracker.h>

#include <common/time_helper.h>
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
				struct eod_datafeed_storage_manager_helper : public eod_datafeed_storage_manager
				{
					common::shared_name_storage names;
					eod_datafeed_storage_manager_helper(){}
					virtual ~eod_datafeed_storage_manager_helper(){}
					virtual const common::shared_name_storage& stock_names()
					{
						return names;
					}
				};

				void eod_datafeed_storage_multithread_read_datafeed_performance_tests_helper( const size_t thread_amount )
				{
					using namespace boost::filesystem;

					eod_datafeed_storage_manager_helper m;
					const long from = common::create_eod_time( 2008, 01, 01 );
					const long to = common::create_eod_time( 2008, 12, 31 );

					static const std::string binary_datafeed_folder = SOURCE_DIR "/data/binary_yahoo_datafeed";
					if ( !exists( binary_datafeed_folder ) )
						return;

					size_t u = 0;
					for( directory_iterator i( binary_datafeed_folder ), end ; i != end && u < 150 ; ++i, ++u  )
						m.names << i->path().filename();

					eod_datafeed_storage storage( m, SOURCE_DIR "/data/binary_yahoo_datafeed", from, to );
					storage.multithread_read_datafeed();
				}
			}
			void eod_datafeed_storage_constructor_tests()
			{
				eod_datafeed_storage_manager_helper m;
				BOOST_CHECK_THROW( eod_datafeed_storage( m, "", 0, 0 ), std::exception );
				BOOST_CHECK_THROW( eod_datafeed_storage( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 0 ), std::exception );
				BOOST_CHECK_NO_THROW( eod_datafeed_storage( m, SOURCE_DIR "/tests/data/binary_data_example/", 0, 1 ) );
			}
			void eod_datafeed_storage_read_datafeed_tests()
			{
				eod_datafeed_storage_manager_helper m;
				const long from = common::create_eod_time( 2008, 01, 01 );
				const long to = common::create_eod_time( 2008, 12, 31 );

				m.names << "aapl";

				BOOST_CHECK_THROW( eod_datafeed_storage eds( m, SOURCE_DIR "/tests/data/binary_data_example/", from, to ), std::exception );

				m.names.del_name( "aapl" );

				m.names << "a" << "amh" << "brkr";

				BOOST_CHECK_NO_THROW( eod_datafeed_storage eds( m, SOURCE_DIR "/tests/data/binary_data_example/", from, to ) );
				eod_datafeed_storage eds( m, SOURCE_DIR "/tests/data/binary_data_example/", from, to );
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

				eod_datafeed_storage_manager_helper m;
				for( directory_iterator i( binary_datafeed_folder ), end ; i != end ; ++i  )
					m.names << i->path().filename();

				eod_datafeed_storage eds( m, binary_datafeed_folder, 0, 60000 );
				BOOST_CHECK_NO_THROW( eds.multithread_read_datafeed() );
			}
		}
	}
}
