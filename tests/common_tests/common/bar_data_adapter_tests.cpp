#include <test_registrator.h>

#include <common/bar_data_adapter.h>

using namespace stsc::common;

namespace stsc
{
	namespace tests_
	{
		namespace common
		{
			void bar_data_adapter_tests()
			{
				price_bar pb;
				pb.open_ = 4.0;
				pb.close_ = 2.0;
				pb.high_ = 6.0;
				pb.low_ = 1.0;
				pb.volume_ = 15.0;

				BOOST_CHECK_EQUAL( bar_data_adapter< bar_data_type::open >().get( pb ), 4.0 );
				BOOST_CHECK_EQUAL( bar_data_adapter< bar_data_type::close >().get( pb ), 2.0 );
				BOOST_CHECK_EQUAL( bar_data_adapter< bar_data_type::low >().get( pb ), 1.0 );
				BOOST_CHECK_EQUAL( bar_data_adapter< bar_data_type::high >().get( pb ), 6.0 );
				BOOST_CHECK_EQUAL( bar_data_adapter< bar_data_type::volume >().get( pb ), 15.0 );
			}
		}
	}
}
