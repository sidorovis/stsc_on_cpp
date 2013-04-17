#include <test_registrator.h>

#include <series_storage/vector_serie.h>

using namespace stsc::engine::series_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace series_storage
			{
				void vector_serie_unit_tests()
				{
					typedef vector_serie< int, 10, 30000 > v_int_type;
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

					BOOST_CHECK_NO_THROW( v_int.insert( 30005, 4352 ) );
					BOOST_CHECK_EQUAL( v_int.at( 30005 ), 4352ul );

					BOOST_CHECK_NO_THROW( v_int.container_check( typeid( std::vector< boost::shared_ptr< int >  > ) ) );
					BOOST_CHECK_THROW( v_int.container_check( typeid( std::vector< boost::shared_ptr< short >  > ) ), std::logic_error );

					boost::shared_ptr< serie< int > > v_int_ptr( new v_int_type() );

					BOOST_CHECK_NO_THROW( v_int_ptr->container_check( typeid( std::vector< boost::shared_ptr< int >  > ) ) );
					BOOST_CHECK_THROW( v_int_ptr->container_check( typeid( std::vector< boost::shared_ptr< short >  > ) ), std::logic_error );
				}
			}
		}
	}
}
