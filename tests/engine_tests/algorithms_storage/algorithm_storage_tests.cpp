#include <test_registrator.h>

#include <algorithm_storage.h>

#include <algorithm_examples.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			void algorithm_storage_unit_tests()
			{
				using namespace stsc::engine::algorithms_storage;
				using namespace stsc::engine;

				typedef algorithms_storage::on_stock_test_algorithm on_stock_test_algorithm;

				on_stock_test_algorithm* a = create_algorithm< on_stock_test_algorithm >( "name" ); 
				BOOST_CHECK_EQUAL( a != NULL, true );

				typed_algorithm< on_stock_test_algorithm > ptr = algorithm_storage().create_on_stock< on_stock_test_algorithm >( "name" );
				BOOST_CHECK_EQUAL( ptr->name(), a->name() );
			}
		}
	}
}
