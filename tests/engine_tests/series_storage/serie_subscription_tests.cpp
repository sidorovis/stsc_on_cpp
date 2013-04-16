#include <test_registrator.h>

#include <series_storage/serie_subscription.h>

#include <series_storage/map_serie.h>

using namespace stsc::engine::series_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace series_storage
			{
				void serie_subscription_unit_tests()
				{
					typedef map_serie< int > msi;
					msi s;
					BOOST_CHECK_NO_THROW( make_subscription( s ).subscription_check( typeid( int ) ) );
					serie_subscription< int > ss = make_subscription( s );
					s.insert( 14ul, 56 );
					BOOST_CHECK_EQUAL( ss.at( 14ul ), 56 );
				}
			}
		}
	}
}

