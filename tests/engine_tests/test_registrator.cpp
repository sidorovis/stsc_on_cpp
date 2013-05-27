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

	using namespace stsc::tests_::engine;

	ts1->add( BOOST_TEST_CASE( &details_parameter_tests ) );
	ts1->add( BOOST_TEST_CASE( &details_parameter_list_tests ) );
	ts1->add( BOOST_TEST_CASE( &details_execution_tests ) );
	ts1->add( BOOST_TEST_CASE( &details_execution_list_tests ) );

	ts1->add( BOOST_TEST_CASE( &simulation_configuration_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_line_index_str_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_trim_line_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_check_and_append_next_line_unit_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_comment_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_delete_brackets_from_parameter_value_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_process_instrument_list_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_divide_assignment_line_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_generate_execution_ptr_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_process_assignment_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_process_line_tests ) );
	ts1->add( BOOST_TEST_CASE( &simulation_configuration_read_unit_tests ) );

	ts1->add( BOOST_TEST_CASE( &algorithm_manager_constructor_tests ) );

	ts1->add( BOOST_TEST_CASE( &algorithm_manager_create_on_stock_algorithm_tests ) );
	ts1->add( BOOST_TEST_CASE( &algorithm_manager_create_on_bar_algorithm_tests ) );
	ts1->add( BOOST_TEST_CASE( &algorithm_manager_create_on_period_algorithm_tests ) );

	ts1->add( BOOST_TEST_CASE( &simulator_constructor_tests ) );

	return ts1;
}

