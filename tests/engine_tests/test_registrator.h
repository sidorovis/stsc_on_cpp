#include <boost/test/test_tools.hpp>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace series_storage
			{
				void map_serie_unit_tests();
				void vector_serie_unit_tests();
			}
			namespace algorithms_storage
			{
				void details_algorithm_prototypes_constructor_tests();

				void on_stock_algorithm_tests();
				void on_bar_algorithm_tests();
				void on_period_algorithm_tests();
			}

			namespace algorithms
			{
				void details_moving_median_constructor_tests();
				void details_moving_median_simple_work_tests();
				
				void moving_median_series_constructor_tests();
				void moving_median_series_simple_work_tests();

				void moving_median_indicator_constructor_tests();
				void moving_median_indicator_simple_work_tests();
			}

			void details_parameter_tests();
			void details_parameter_list_tests();
			void details_execution_tests();
			void details_execution_list_tests();

			void simulation_configuration_constructor_tests();
			void simulation_configuration_line_index_str_tests();
			void simulation_configuration_trim_line_tests();
			void simulation_configuration_check_and_append_next_line_unit_tests();
			void simulation_configuration_comment_tests();
			void simulation_configuration_delete_brackets_from_parameter_value_tests();
			void simulation_configuration_process_instrument_list_tests();
			void simulation_configuration_divide_assignment_line_tests();
			void simulation_configuration_generate_execution_ptr_tests();
			void simulation_configuration_process_assignment_tests();

			void simulation_configuration_process_line_tests();
			void simulation_configuration_read_unit_tests();

			void algorithm_manager_constructor_tests();

			void algorithm_manager_create_on_stock_algorithm_tests();
			void algorithm_manager_create_on_bar_algorithm_tests();
			void algorithm_manager_create_on_period_algorithm_tests();

			void simulator_constructor_tests();
		}
	}
}
