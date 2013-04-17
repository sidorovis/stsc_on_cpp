#include <test_registrator.h>

#include <algorithms_storage/algorithms_engine.h>

using namespace stsc::engine::algorithms_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms_storage
			{
				void algorithms_constructor_tests()
				{
					BOOST_CHECK_NO_THROW( algorithms_engine() );
				}
			}
		}
	}
}