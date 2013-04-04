#include <test_registrator.h>

#include <signal_storages/map_serie.h>

using namespace stsc::engine::signal_storages;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace signal_storages
			{
				void map_serie_unit_tests()
				{
					typedef map_serie< int > ms_int_type;
					ms_int_type ms_int;
					BOOST_CHECK_EQUAL( ms_int.size(), 0ul );
					BOOST_CHECK_EQUAL( ms_int.empty(), true );
					common::bar_type k1, k2, k3, k4, k5, k6;
					BOOST_CHECK_NO_THROW( ms_int.insert( k1, new int( 4 ) ) );
					BOOST_CHECK_THROW( ms_int.insert( k1, new int( 4 ) ), std::exception );
					BOOST_CHECK_NO_THROW( ms_int.insert( k2, new int( 4 ) ) );
					BOOST_CHECK_NO_THROW( ms_int.insert( k3, new int( 6 ) ) );
					BOOST_CHECK_NO_THROW( ms_int.insert( k4, new int( 7 ) ) );
					BOOST_CHECK_NO_THROW( ms_int.insert( k5, new int( 1231 ) ) );

					BOOST_CHECK_NO_THROW( ms_int.ptr_at( k1 ) );
					BOOST_CHECK_THROW( ms_int.at( k6 ), std::exception );

					BOOST_CHECK_EQUAL( *ms_int.ptr_at( k1 ), 4 );
					BOOST_CHECK_EQUAL( *ms_int.ptr_at( k3 ), 6 );
					BOOST_CHECK_EQUAL( *ms_int.ptr_at( k2 ), 4 );
					BOOST_CHECK_EQUAL( *ms_int.ptr_at( k5 ), 1231 );
					BOOST_CHECK_EQUAL( ms_int.at( k3 ), 6 );
					BOOST_CHECK_EQUAL( ms_int.at( k2 ), 4 );
				}
			}
		}
	}
}
