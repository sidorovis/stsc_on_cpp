#include <test_registrator.h>

#include <common/bar_types.h>

using namespace stsc::common;

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			//
			void bar_type_constructor_tests()
			{
				BOOST_CHECK_NO_THROW( bar_data_type::value );

				BOOST_CHECK_NO_THROW( bar_data_type::open );
				BOOST_CHECK_NO_THROW( bar_data_type::high );
				BOOST_CHECK_NO_THROW( bar_data_type::low );
				BOOST_CHECK_NO_THROW( bar_data_type::close );

				BOOST_CHECK_NO_THROW( bar_data_type::volume );

				bar_type bar;
				bar.time_ = 156l;
				BOOST_CHECK_EQUAL( bar.time_, 156l );
			}
			void bar_type_ostream_operator_tests()
			{
				bar_type bar;
				bar.time_ = 1565345352l;
				std::stringstream stream;
				stream << bar;
				BOOST_CHECK_EQUAL( stream.str(), "bar( 1565345352 )" );
			}
			void price_bar_constructor_tests()
			{
				price_bar bar;
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
			void price_bar_ostream_operator_tests()
			{
				price_bar bar;
				bar.time_ = 156l;
				bar.open_ = 45.65f;
				bar.close_ = 45.34f;
				bar.high_ = 45.67f;
				bar.low_ = 45.33f;
				bar.volume_ = 100000.0f;
				std::stringstream stream;
				stream.setf( std::ios::fixed,std::ios::floatfield );
				stream.precision( 3 );
				stream << bar;
				BOOST_CHECK_EQUAL( stream.str(), "bar( 156||45.650|45.670|45.330|45.340 100000.000 )" );
			}
			//
			void on_stock_bar_tests()
			{
				price_bar b;
				BOOST_CHECK_NO_THROW( on_stock_bar( b, 14 ) );
			}
			void on_bar_tests()
			{
				bar_type b;
				BOOST_CHECK_NO_THROW( on_bar( b, 15 ) );
			}
			void on_period_tests()
			{
				bar_type b;
				BOOST_CHECK_NO_THROW( on_period( b, 16 ) );
			}
		}
	}
}
