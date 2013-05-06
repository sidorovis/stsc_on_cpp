#include <test_registrator.h>

#include <common/time_helper.h>

using namespace stsc::common;

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			void create_extract_eod_time_tests()
			{
				BOOST_CHECK_NO_THROW( create_eod_time( 2000, 11, 23 ) );
				BOOST_CHECK_EQUAL( create_eod_time( 2000, 11, 23 ), 36851 );
				short year = 0, month = 0, day = 0;
				BOOST_CHECK_NO_THROW( extract_eod_time( 36851, year, month, day ) );
				BOOST_CHECK_EQUAL( year, 2000 );
				BOOST_CHECK_EQUAL( month, 11 );
				BOOST_CHECK_EQUAL( day, 23 );
			}
		}
	}
}
