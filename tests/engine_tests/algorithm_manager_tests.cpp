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
				void add_stocks( common::shared_name_storage& am )
				{
					am << "aapl" << "bidu" << "c" << "spy" << "qqq";
				}
			}
			void algorithm_manager_constructor_tests()
			{
				common::shared_name_storage stock_names;
				BOOST_CHECK_NO_THROW( algorithm_manager am( stock_names ) );
			}
			void algorithm_manager_create_on_stock_algorithm_tests()
			{
				common::shared_name_storage stock_names;
				add_stocks( stock_names );
				algorithm_manager am( stock_names );

				BOOST_CHECK_NO_THROW( am.create_on_stock_algorithm< algorithms_storage::on_stock_test_algorithm >( "Alai Oli", 0 ) );
				BOOST_CHECK_THROW( am.create_on_stock_algorithm< algorithms_storage::on_stock_test_algorithm >( "Alai Oli", 0 ), std::exception );
			}
			void algorithm_manager_create_on_bar_algorithm_tests()
			{
				common::shared_name_storage stock_names;
				add_stocks( stock_names );
				algorithm_manager am( stock_names );
				
				BOOST_CHECK_NO_THROW( am.create_on_bar_algorithm< algorithms_storage::on_bar_test_algorithm >( "Beatles", 0 ) );
				BOOST_CHECK_NO_THROW( am.create_on_bar_algorithm< algorithms_storage::on_bar_test_algorithm >( "New Beatles", 0 ) );
				BOOST_CHECK_THROW( am.create_on_bar_algorithm< algorithms_storage::on_bar_test_algorithm >( "Beatles", 0 ), std::exception );
			}
			void algorithm_manager_create_on_period_algorithm_tests()
			{
				common::shared_name_storage stock_names;
				add_stocks( stock_names );
				algorithm_manager am( stock_names );

				BOOST_CHECK_NO_THROW( am.create_on_period_algorithm< algorithms_storage::on_period_test_algorithm >( "Bob Marley", 0 ) );
				BOOST_CHECK_NO_THROW( am.create_on_period_algorithm< algorithms_storage::on_period_test_algorithm >( "Demian Marley", 0 ) );
				BOOST_CHECK_THROW( am.create_on_period_algorithm< algorithms_storage::on_period_test_algorithm >( "Demian Marley", 0 ), std::exception );
			}
		}
	}
}
