#include <test_registrator.h>

#include <series_storage/series.h>

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
				void details_on_stock_series_storage_unit_tests()
				{
					typedef on_stock_series_storage< int > storage;
					BOOST_CHECK_EQUAL( typeid( storage::typed_serie ) == typeid( serie< int > ), true );
					BOOST_CHECK_EQUAL( typeid( storage::serie_ptr ) == typeid( boost::shared_ptr< serie< int > > ), true );
					BOOST_CHECK_EQUAL( typeid( storage::series ) == typeid( std::map< common::shared_string, boost::shared_ptr< serie< int > > > ), true );
				}
			}
		}
	}
}

