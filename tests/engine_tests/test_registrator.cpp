#include <test_registrator.h>

#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* ts1 = BOOST_TEST_SUITE( "stsc engine tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );

	using namespace stsc::tests_::engine;

	ts1->add( BOOST_TEST_CASE( &signal_vector_unit_tests ) );
	ts1->add( BOOST_TEST_CASE( &details_signals_storage_unit_tests ) );
	
	ts1->add( BOOST_TEST_CASE( &strategies_engine_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &algorithm_prototypes_constructor_tests ) );


	//ts1->add( BOOST_TEST_CASE( &details_algorithms_storage_constructor_tests ) );
	//ts1->add( BOOST_TEST_CASE( &details_signals_storage_constructor_tests ) );
	//ts1->add( BOOST_TEST_CASE( &engine_storage_constructor_tests ) );
	//ts1->add( BOOST_TEST_CASE( &engine_storage_registrate_algorithm_tests ) );

	ts1->add( BOOST_TEST_CASE( &moving_median_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &moving_median_simple_work_tests ) );

	ts1->add( BOOST_TEST_CASE( &moving_median_indicator_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &moving_median_indicator_simple_work_tests ) );

	return ts1;
}

