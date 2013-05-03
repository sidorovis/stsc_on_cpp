#include <test_registrator.h>

#include <algorithm_manager.h>

#include <algorithm_examples.h>

using namespace stsc::engine;
using namespace stsc::engine::algorithms_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace
			{
				void add_stocks( algorithm_manager& am )
				{
					const size_t stocks_size = 5;
					const char* stocks[ stocks_size ] = { "aapl", "bidu", "c", "spy", "qqq" };
					am.add_stocks( stocks + 0, stocks + stocks_size );
				}
			}
			void algorithm_manager_constructor_tests()
			{
				BOOST_CHECK_NO_THROW( algorithm_manager() );
			}
			void algorithm_manager_add_stocks_tests()
			{
				algorithm_manager am;
				BOOST_CHECK_NO_THROW( add_stocks( am ) )
				BOOST_CHECK_NO_THROW( add_stocks( am ) )
			}
			void algorithm_manager_create_on_stock_algorithm_tests()
			{
				algorithm_manager am;
				add_stocks( am );

				BOOST_CHECK_NO_THROW( am.create_on_stock_algorithm< algorithms_storage::on_stock_test_algorithm >( "Alai Oli", 0 ) );
				BOOST_CHECK_THROW( am.create_on_stock_algorithm< algorithms_storage::on_stock_test_algorithm >( "Alai Oli", 0 ), std::exception );
			}
			void algorithm_manager_create_on_bar_algorithm_tests()
			{
				algorithm_manager am;
				add_stocks( am );
				
				BOOST_CHECK_NO_THROW( am.create_on_bar_algorithm< algorithms_storage::on_bar_test_algorithm >( "Beatles", 0 ) );
				BOOST_CHECK_NO_THROW( am.create_on_bar_algorithm< algorithms_storage::on_bar_test_algorithm >( "New Beatles", 0 ) );
				BOOST_CHECK_THROW( am.create_on_bar_algorithm< algorithms_storage::on_bar_test_algorithm >( "Beatles", 0 ), std::exception );
			}
			void algorithm_manager_create_on_period_algorithm_tests()
			{
				algorithm_manager am;
				add_stocks( am );

				BOOST_CHECK_NO_THROW( am.create_on_period_algorithm< algorithms_storage::on_period_test_algorithm >( "Bob Marley", 0 ) );
				BOOST_CHECK_NO_THROW( am.create_on_period_algorithm< algorithms_storage::on_period_test_algorithm >( "Demian Marley", 0 ) );
				BOOST_CHECK_THROW( am.create_on_period_algorithm< algorithms_storage::on_period_test_algorithm >( "Demin Marley", 0 ), std::exception );
			}
		}
	}
}
