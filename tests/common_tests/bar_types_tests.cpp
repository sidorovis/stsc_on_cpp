#include <test_registrator.h>

#include <bar_types.h>

using namespace stsc::common;

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			void bar_types_possible_values_tests()
			{
				BOOST_CHECK_EQUAL( sizeof( float ) <= sizeof( double ), true );
			}
			void specialized_bar_types_tests()
			{
				BOOST_CHECK_EQUAL( typeid( float_bar_type::float_type ) == typeid( float ), true );
				BOOST_CHECK_EQUAL( typeid( double_bar_type::float_type ) == typeid( double ), true );
			}
			void bar_type_constructor_tests()
			{
				float_bar_type bar;
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
				float_bar_type bar;
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
