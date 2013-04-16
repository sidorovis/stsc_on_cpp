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

				void serie_subscription_unit_tests();

				void details_on_stock_series_storage_unit_tests();
			}
			namespace algorithms_storage
			{
				void details_algorithm_prototypes_constructor_tests();

				void on_stock_algorithm_tests();
			}

			//void signal_vector_unit_tests();
			//void details_signals_storage_unit_tests();

			//void strategies_engine_constructor_tests();
			//void algorithm_prototypes_constructor_tests();

			//void algorithm_prototype_constructor_tests();

			//void moving_median_constructor_tests();
			//void moving_median_simple_work_tests();
			//
			//void moving_median_series_constructor_tests();
			//void moving_median_series_simple_work_tests();

			//void moving_median_indicator_constructor_tests();
			//void moving_median_indicator_simple_work_tests();
		}
	}
}
