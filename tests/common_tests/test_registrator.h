#include <boost/test/test_tools.hpp>

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			void create_extract_eod_time_tests();

			void create_shared_string_tests();

			void check_existance_of_basic_types();
			void bar_type_constructor_tests();
			void bar_type_ostream_operator_tests();

			void price_bar_constructor_tests();
			void price_bar_ostream_operator_tests();

			void bar_data_adapter_tests();

			void on_stock_bar_tests();
			void on_bar_tests();
			void on_period_tests();

			void signal_subtypes_tests();

			void close_signal_constructor_tests();
			void close_signal_type_tests();
			void open_signal_constructor_tests();
			void open_signal_type_tests();
			void signal_ostream_operator_tests();
		}
	}
}
