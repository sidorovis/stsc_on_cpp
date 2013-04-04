#include <test_registrator.h>

#include <signal_storages/vector_serie.h>

using namespace stsc::engine::signal_storages;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace signal_storages
			{
				void vector_serie_unit_tests()
				{
					typedef vector_serie< int, 0, 10, 30000 > v_int_type;
					v_int_type v_int;
					BOOST_CHECK_EQUAL( v_int.size(), 0ul );
					BOOST_CHECK_EQUAL( v_int.empty(), true );
					for ( size_t i = 0 ; i < 30000 ; ++i )
						if ( i % 3 == 0 )
							BOOST_CHECK_NO_THROW( v_int.insert( i, static_cast< int >( i + 10 ) ) );
					BOOST_CHECK_EQUAL( v_int.at( 0 ), 10ul );
					BOOST_CHECK_THROW( v_int.at( 1 ), std::exception );
					BOOST_CHECK_NO_THROW( v_int.ptr_at( 1 ) );
					BOOST_CHECK_EQUAL( v_int.ptr_at( 1 ) == NULL, true );
				}
			}
		}
	}
}
