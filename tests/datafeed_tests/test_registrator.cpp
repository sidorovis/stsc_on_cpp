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

	ts1->add( BOOST_TEST_CASE( &period_header_sizeof_tests ) );
	ts1->add( BOOST_TEST_CASE( &period_constructor_tests ) );

	ts1->add( BOOST_TEST_CASE( &write_read_unit_tests ) );

	return ts1;
}

