#include <algorithms_storage/algorithm_examples.h>

#include <series_storage/map_serie.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms_storage
			{
				on_stock_test_algorithm::on_stock_test_algorithm( const std::string& name )
					: typed_algorithm( name )
				{
				}
				void on_stock_test_algorithm::process( const bar_type& b )
				{
					if ( b.value.close_ == 0.56f )
						register_signal( b, 45.0 );
					if ( b.value.close_ == 5.27f )
						register_signal( b, -89.5 );
				}
				on_stock_test_algorithm::serie_ptr on_stock_test_algorithm::serie_prototype() const
				{
					return serie_ptr( new stsc::engine::series_storage::map_serie< signal_type >() );
				}
			}
		}
	}
}
