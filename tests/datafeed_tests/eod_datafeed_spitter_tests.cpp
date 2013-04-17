#include <test_registrator.h>

#include <time_tracker.h>

#include <time_helper.h>

#include <eod_datafeed_storage.h>
#include <eod_datafeed_spitter.h>

using namespace stsc::datafeed;

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			namespace
			{
				struct datafeed_manager_test_helper : public datafeed_manager
				{
					boost::mutex m;
					std::vector< std::string > actions_;
					std::vector< long > times_;
					virtual void new_bar_on_stock( const common::on_stock_bar& bar )
					{
						std::stringstream s;
						s << "nbos|" << *bar.stock_name << "|" << bar.value;
						boost::mutex::scoped_lock lock( m );
						times_.push_back( bar.value.time_ );
						actions_.push_back( s.str() );
					}
					virtual void new_bar_on_bar( const common::on_bar& bar )
					{
						std::stringstream s;
						s << "nbob|" << bar.value;
						boost::mutex::scoped_lock lock( m );
						times_.push_back( bar.value.time_ );
						actions_.push_back( s.str() );
					}
					virtual void new_bar_on_period( const common::on_period& bar )
					{
						std::stringstream s;
						s << "nbop|" << bar.value;
						boost::mutex::scoped_lock lock( m );
						times_.push_back( bar.value.time_ );
						actions_.push_back( s.str() );
					}
					virtual void file_reading_error( const std::string& file_path )
					{
						boost::mutex::scoped_lock lock( m );
						actions_.push_back( "fre|" + file_path );
					}
				public:
					virtual ~datafeed_manager_test_helper(){}
				};
				struct datafeed_manager_non_synchronized_test_helper : public datafeed_manager
				{
					virtual void new_bar_on_stock( const common::on_stock_bar& bar )
					{
						std::string a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
						for ( int i = 0 ; i < 1000 ; ++i )
							std::next_permutation( a.begin(), a.end() );
					}
				public:
					virtual ~datafeed_manager_non_synchronized_test_helper(){}
					};
				//
				size_t eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( const short year, const size_t stock_size, const size_t thread_amount, const size_t result )
				{
					using namespace boost::filesystem;

					system_utilities::common::time_tracker tt;
					datafeed_manager_test_helper m;
					const long from = common::create_eod_time( year, 01, 01 );
					const long to = common::create_eod_time( 2013, 12, 31 );

					static const std::string binary_datafeed_folder = SOURCE_DIR "/data/binary_yahoo_datafeed";
					if ( !exists( binary_datafeed_folder ) )
						return 0ul;

					eod_datafeed_storage storage( m, SOURCE_DIR "/data/binary_yahoo_datafeed", from, to );
					size_t u = 0;
					for( directory_iterator i( binary_datafeed_folder ), end ; i != end && u < stock_size ; ++i, ++u  )
						BOOST_CHECK_NO_THROW( storage.add_stock_to_parse( i->path().filename() ) );
					storage.multithread_read_datafeed();
					eod_datafeed_spitter spitter( storage );
					BOOST_CHECK_NO_THROW( spitter.multithread_spit_datafeed( thread_amount ) );
					BOOST_CHECK_NO_THROW( spitter.spit_datafeed() );
					BOOST_CHECK_EQUAL( m.actions_.size(), result );
					for ( size_t i = 1 ; i < m.times_.size() ; ++i )
						BOOST_CHECK_EQUAL( m.times_[ i - 1 ] <= m.times_[ i ], true );
					return tt.milliseconds();
				}
			}

			void eod_datafeed_spitter_constructor_tests()
			{
				datafeed_manager m;
				const long from = common::create_eod_time( 2008, 01, 01 );
				const long to = common::create_eod_time( 2008, 12, 31 );
				eod_datafeed_storage storage( m, SOURCE_DIR "/tests/data/binary_data_example/", from, to );
				storage.add_stock_to_parse( "a" ).add_stock_to_parse( "brkr" ).add_stock_to_parse( "xynh" );
				storage.add_stock_to_parse( "amh" ).add_stock_to_parse( "fve" ).add_stock_to_parse( "idai" );
				storage.add_stock_to_parse( "muv" ).add_stock_to_parse( "sior" ).add_stock_to_parse( "tpam" );
				storage.read_datafeed();
				BOOST_CHECK_NO_THROW( eod_datafeed_spitter spitter( storage ) );
			}
			void eod_datafeed_spitter_spit_datafeed_tests()
			{
				datafeed_manager_test_helper m;
				const long from = common::create_eod_time( 2008, 01, 01 );
				const long to = common::create_eod_time( 2008, 12, 31 );
				eod_datafeed_storage storage( m, SOURCE_DIR "/tests/data/binary_data_example/", from, to );
				storage.add_stock_to_parse( "a" ).add_stock_to_parse( "brkr" ).add_stock_to_parse( "xynh" );
				storage.add_stock_to_parse( "amh" ).add_stock_to_parse( "fve" ).add_stock_to_parse( "idai" );
				storage.add_stock_to_parse( "muv" ).add_stock_to_parse( "sior" ).add_stock_to_parse( "tpam" );
				storage.read_datafeed();
				eod_datafeed_spitter spitter( storage );
				BOOST_CHECK_NO_THROW( spitter.spit_datafeed() );
				BOOST_CHECK_EQUAL( m.actions_.size(), 2261ul );
				for ( size_t i = 1 ; i < m.times_.size() ; ++i )
					BOOST_CHECK_EQUAL( m.times_[ i - 1 ] <= m.times_[ i ], true );
			}
			void eod_datafeed_spitter_multithread_spit_datafeed_tests()
			{
				datafeed_manager_test_helper m;
				const long from = common::create_eod_time( 2008, 01, 01 );
				const long to = common::create_eod_time( 2008, 12, 31 );
				eod_datafeed_storage storage( m, SOURCE_DIR "/tests/data/binary_data_example/", from, to );
				storage.add_stock_to_parse( "a" ).add_stock_to_parse( "brkr" ).add_stock_to_parse( "xynh" );
				storage.add_stock_to_parse( "amh" ).add_stock_to_parse( "fve" ).add_stock_to_parse( "idai" );
				storage.add_stock_to_parse( "muv" ).add_stock_to_parse( "sior" ).add_stock_to_parse( "tpam" );
				storage.read_datafeed();
				eod_datafeed_spitter spitter( storage );
				BOOST_CHECK_NO_THROW( spitter.multithread_spit_datafeed() );
				BOOST_CHECK_EQUAL( m.actions_.size(), 2261ul );
				for ( size_t i = 1 ; i < m.times_.size() ; ++i )
					BOOST_CHECK_EQUAL( m.times_[ i - 1 ] <= m.times_[ i ], true );
			}
			void eod_datafeed_spitter_multithread_spit_datafeed_performance_tests()
			{
				for ( size_t u = 1 ; u < 8 ; ++u )
				{
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2013, 10ul, u, 503ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2013, 30ul, u, 1258ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2013, 90ul, u, 3547ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2012, 10ul, u, 3286ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2012, 30ul, u, 8510ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2012, 90ul, u, 23205ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2011, 10ul, u, 5944ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2011, 30ul, u, 15721ul );
					eod_datafeed_spitter_multithread_spit_datafeed_performance_tests_helper( 2011, 90ul, u, 43359ul );
				}
			}
		}
	}
}
