#include <boost/test/test_tools.hpp>

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			namespace binary
			{
				void period_header_sizeof_tests();
				void period_constructor_tests();

				void period_write_read_unit_tests();
				void period_write_read_part_unit_tests();
			}
			namespace csv
			{
				void yahoo_finance_reader_constructor_tests();
				void yahoo_finance_reader_unit_tests();
				void yahoo_finance_to_binary_data_unit_tests();
				void yahoo_finance_to_binary_data_integration_tests();

				void yahoo_finance_reader_performance_tests();
			}

			void eod_datafeed_storage_constructor_tests();
			void eod_datafeed_storage_read_datafeed_tests();
			void eod_datafeed_storage_multithread_read_datafeed_tests();
			void eod_datafeed_storage_read_performance_tests();

			void eod_datafeed_spitter_constructor_tests();
			void eod_datafeed_spitter_spit_datafeed_tests();
			void eod_datafeed_spitter_multithread_spit_datafeed_tests();
			void eod_datafeed_spitter_multithread_spit_datafeed_performance_tests();
		}
	}
}
