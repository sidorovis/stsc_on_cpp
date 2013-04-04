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
					BOOST_CHECK_NO_THROW( ms_int.insert( 1, new int( 4 ) ) );
					BOOST_CHECK_THROW( ms_int.insert( 1, new int( 4 ) ), std::exception );
					BOOST_CHECK_NO_THROW( ms_int.insert( 2, new int( 4 ) ) );
					BOOST_CHECK_NO_THROW( ms_int.insert( 3, new int( 6 ) ) );
					BOOST_CHECK_NO_THROW( ms_int.insert( 4, new int( 7 ) ) );
					BOOST_CHECK_NO_THROW( ms_int.insert( 5, new int( 1231 ) ) );

					BOOST_CHECK_NO_THROW( ms_int.ptr_at( 1 ) );
					BOOST_CHECK_THROW( ms_int.at( 6 ), std::exception );

					BOOST_CHECK_EQUAL( *ms_int.ptr_at( 1 ), 4 );
					BOOST_CHECK_EQUAL( *ms_int.ptr_at( 3 ), 6 );
					BOOST_CHECK_EQUAL( *ms_int.ptr_at( 2 ), 4 );
					BOOST_CHECK_EQUAL( *ms_int.ptr_at( 5 ), 1231 );
					BOOST_CHECK_EQUAL( ms_int.at( 3 ), 6 );
					BOOST_CHECK_EQUAL( ms_int.at( 2 ), 4 );
				}
			}
		}
	}
}
