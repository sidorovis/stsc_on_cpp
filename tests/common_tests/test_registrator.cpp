#include <test_registrator.h>

#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* ts1 = BOOST_TEST_SUITE( "stsc common tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );

	using namespace stsc::tests_::common;

	ts1->add( BOOST_TEST_CASE( &create_extract_eod_time_tests ) );

	ts1->add( BOOST_TEST_CASE( &create_shared_string_tests ) );

	ts1->add( BOOST_TEST_CASE( &check_existance_of_basic_types ) );
	ts1->add( BOOST_TEST_CASE( &bar_type_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &bar_type_ostream_operator_tests ) );
	ts1->add( BOOST_TEST_CASE( &price_bar_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &price_bar_ostream_operator_tests ) );

	ts1->add( BOOST_TEST_CASE( &bar_data_adapter_tests ) );

	ts1->add( BOOST_TEST_CASE( &on_stock_bar_tests ) );
	ts1->add( BOOST_TEST_CASE( &on_bar_tests ) );
	ts1->add( BOOST_TEST_CASE( &on_period_tests ) );

	ts1->add( BOOST_TEST_CASE( &signal_subtypes_tests ) );
	ts1->add( BOOST_TEST_CASE( &close_signal_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &close_signal_type_tests ) );
	ts1->add( BOOST_TEST_CASE( &open_signal_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &open_signal_type_tests ) );
	ts1->add( BOOST_TEST_CASE( &signal_ostream_operator_tests ) );

	return ts1;
}

