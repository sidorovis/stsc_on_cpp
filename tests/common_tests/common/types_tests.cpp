#include <test_registrator.h>

#include <common/types.h>

using namespace stsc::common;

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			void check_existance_of_basic_types()
			{
				BOOST_CHECK_NO_THROW( index( 14 ) );
				BOOST_CHECK_NO_THROW( shared_string( new std::string("hello tests") ) );
			}

			void create_shared_string_tests()
			{
				BOOST_CHECK_EQUAL( make_shared_string( "hello" )->c_str(), "hello" );
			}
		}
	}
}