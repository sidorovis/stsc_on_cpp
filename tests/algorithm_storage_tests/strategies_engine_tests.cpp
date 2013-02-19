#include <test_registrator.h>

#include <strategies_engine.h>

using namespace stsc::algorithm_storage;

namespace stsc
{
	namespace tests_
	{
		namespace algorithm_storage
		{
			void strategies_engine_constructor_tests()
			{
				BOOST_CHECK_NO_THROW( strategies_engine es );
			}
		}
	}
}

