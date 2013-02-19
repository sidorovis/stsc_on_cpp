#include <test_registrator.h>

#include <bar_types.h>

using namespace stsc::common;

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			void bar_type_constructor_tests()
			{
				bar_type bar;
				bar.open_ = 45.65f;
				bar.close_ = 45.34f;
				bar.high_ = 45.67f;
				bar.low_ = 45.33f;
				bar.volume_ = 100000.0f;
				BOOST_CHECK_EQUAL( bar.open_, 45.65f );
				BOOST_CHECK_EQUAL( bar.close_, 45.34f );
				BOOST_CHECK_EQUAL( bar.high_, 45.67f );
				BOOST_CHECK_EQUAL( bar.low_, 45.33f );
				BOOST_CHECK_EQUAL( bar.volume_, 100000.0f );
			}
			void bar_type_ostream_operator_tests()
			{
				bar_type bar;
				bar.open_ = 45.65f;
				bar.close_ = 45.34f;
				bar.high_ = 45.67f;
				bar.low_ = 45.33f;
				bar.volume_ = 100000.0f;
				std::stringstream stream;
				stream << bar;
				BOOST_CHECK_EQUAL( stream.str(), "bar( 45.650|45.670|45.330|45.340 100000.000 )" );
			}
		}
	}
}
