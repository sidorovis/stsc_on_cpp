#include <test_registrator.h>

#include <strategies_engine.h>

#include <algorithm_examples.h>

using namespace stsc::engine;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			void algorithm_prototypes_constructor_tests()
			{
				strategies_engine se;
				on_stock_algorithm_example osae( "osae", se );
				on_bar_algorithm_example obae( "obae", se, "osae" );
			}
		}
	}
}

