#include <test_registrator.h>

#include <series_storage/on_bar_serie.h>

using namespace stsc::engine::series_storage::details;
using namespace stsc::engine::series_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace series_storage
			{
				void details_on_bar_serie_unit_tests()
				{
					typedef on_bar_serie< int > storage;
					BOOST_CHECK_EQUAL( typeid( storage::typed_serie ) == typeid( serie< int > ), true );
					BOOST_CHECK_EQUAL( typeid( storage::serie_ptr ) == typeid( boost::shared_ptr< serie< int > > ), true );
				}
			}
		}
	}
}

