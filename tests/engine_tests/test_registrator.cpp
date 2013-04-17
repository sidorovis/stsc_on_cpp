#include <test_registrator.h>

#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* ts1 = BOOST_TEST_SUITE( "stsc engine tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );

	using namespace stsc::tests_::engine::series_storage;

	ts1->add( BOOST_TEST_CASE( &map_serie_unit_tests ) );
	ts1->add( BOOST_TEST_CASE( &vector_serie_unit_tests ) );

	ts1->add( BOOST_TEST_CASE( &serie_subscription_unit_tests ) );

	ts1->add( BOOST_TEST_CASE( &details_on_stock_series_storage_unit_tests ) );

	using namespace stsc::tests_::engine::algorithms_storage;

	ts1->add( BOOST_TEST_CASE( &details_algorithm_prototypes_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &on_stock_algorithm_tests ) );
	ts1->add( BOOST_TEST_CASE( &on_bar_algorithm_tests ) );
	ts1->add( BOOST_TEST_CASE( &on_period_algorithm_tests ) );

	using namespace stsc::tests_::engine::algorithms;

	ts1->add( BOOST_TEST_CASE( &details_moving_median_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &details_moving_median_simple_work_tests ) );

	ts1->add( BOOST_TEST_CASE( &moving_median_series_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &moving_median_series_simple_work_tests ) );

	ts1->add( BOOST_TEST_CASE( &moving_median_indicator_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &moving_median_indicator_simple_work_tests ) );

	ts1->add( BOOST_TEST_CASE( &algorithms_constructor_tests ) );

	return ts1;
}

