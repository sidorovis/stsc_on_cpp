#include <test_registrator.h>

#include <common/signal_types.h>

using namespace stsc::common;

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			void signal_subtypes_tests()
			{
				BOOST_CHECK_NO_THROW( signal_type::value );
				BOOST_CHECK_NO_THROW( signal_type::open );
				BOOST_CHECK_NO_THROW( signal_type::close );
			}
			void close_signal_constructor_tests()
			{
				BOOST_CHECK_NO_THROW( close_signal cs );
			}
			void close_signal_type_tests()
			{
				BOOST_CHECK_NO_THROW( close_signal().type() );
				BOOST_CHECK_EQUAL( close_signal().type(), signal_type::close );
			}
			//
			void open_signal_constructor_tests()
			{
				BOOST_CHECK_NO_THROW( open_signal::side_long );
				BOOST_CHECK_NO_THROW( open_signal::side_short );
				BOOST_CHECK_NO_THROW( open_signal::side );
				BOOST_CHECK_NO_THROW( open_signal os( open_signal::side_long ) );
			}
			void open_signal_type_tests()
			{
				BOOST_CHECK_EQUAL( open_signal( open_signal::side_long ).type(), signal_type::open );
			}
			//
			void signal_ostream_operator_tests()
			{
				{
					std::stringstream str;
					str << close_signal();
					BOOST_CHECK_EQUAL( str.str(), "signal(close)" );
				}
				{
					std::stringstream str;
					str << open_signal( open_signal::side_long );
					str << open_signal( open_signal::side_short );
					BOOST_CHECK_EQUAL( str.str(), "signal(open|1)signal(open|-1)" );
				}
			}
		}
	}
}
