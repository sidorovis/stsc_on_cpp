#include <test_registrator.h>

#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* ts1 = BOOST_TEST_SUITE( "stsc datafeed tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );

	using namespace stsc::tests_::datafeed::binary;
	using namespace stsc::tests_::datafeed::csv;
	using namespace stsc::tests_::datafeed;

	ts1->add( BOOST_TEST_CASE( &period_header_sizeof_tests ) );
	ts1->add( BOOST_TEST_CASE( &period_constructor_tests ) );

	ts1->add( BOOST_TEST_CASE( &period_write_read_unit_tests ) );
	ts1->add( BOOST_TEST_CASE( &period_write_read_part_unit_tests ) );

	ts1->add( BOOST_TEST_CASE( &yahoo_finance_reader_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &yahoo_finance_reader_unit_tests ) );
	ts1->add( BOOST_TEST_CASE( &yahoo_finance_to_binary_data_unit_tests ) );
	ts1->add( BOOST_TEST_CASE( &yahoo_finance_to_binary_data_integration_tests ) );

	ts1->add( BOOST_TEST_CASE( &eod_datafeed_storage_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &eod_datafeed_storage_read_datafeed_tests ) );
	ts1->add( BOOST_TEST_CASE( &eod_datafeed_storage_multithread_read_datafeed_tests ) );

	ts1->add( BOOST_TEST_CASE( &eod_datafeed_spitter_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &eod_datafeed_spitter_spit_datafeed_tests ) );
	ts1->add( BOOST_TEST_CASE( &eod_datafeed_spitter_multithread_spit_datafeed_tests ) );

	if ( RUN_PERFORMANCE_TESTS )
	{
		ts1->add( BOOST_TEST_CASE( &yahoo_finance_reader_performance_tests ) );
		ts1->add( BOOST_TEST_CASE( &eod_datafeed_storage_read_performance_tests ) ); 
		ts1->add( BOOST_TEST_CASE( &eod_datafeed_spitter_multithread_spit_datafeed_performance_tests ) );
	}

	return ts1;
}

