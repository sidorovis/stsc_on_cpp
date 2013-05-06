#include <test_registrator.h>

#include <simulator.h>

using namespace stsc::engine;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			void simulator_constructor_tests()
			{
				BOOST_CHECK_NO_THROW( simulator() );
			}
		}
	}
}
