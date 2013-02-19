#include <test_registrator.h>

#include <strategies_engine.h>

#include <algorithm_examples.h>

using namespace stsc::algorithm_storage;

namespace stsc
{
	namespace tests_
	{
		namespace algorithm_storage
		{
			void algorithm_prototype_constructor_tests()
			{
				strategies_engine se;
				double_out_algorithm doa( "doa", se );
				void_out_algorithm voa( "voa", se, "doa" );
			}
		}
	}
}

