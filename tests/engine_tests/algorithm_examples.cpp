#include <algorithm_examples.h>

#include <series_storage/map_serie.h>
#include <series_storage/vector_serie.h>

using namespace stsc::engine::algorithms_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms_storage
			{
				on_stock_test_algorithm::on_stock_test_algorithm( const on_stock_algorithm_init& init )
					: typed_algorithm( init, typed_serie_ptr( new double_map_serie() ) )
				{
				}
				on_stock_test_algorithm::~on_stock_test_algorithm()
				{
				}
				void on_stock_test_algorithm::process( const bar_type& b )
				{
					if ( b.value.close_ == 0.56f )
						register_signal( b, 45.0 );
					if ( b.value.close_ == 5.27f )
						register_signal( b, -89.5 );
				}
				//
				on_bar_test_algorithm::on_bar_test_algorithm( const algorithm_init& init )
					: typed_algorithm( init, typed_serie_ptr( new int_map_serie() ) )
				{
				}
				on_bar_test_algorithm::~on_bar_test_algorithm()
				{
				}
				void on_bar_test_algorithm::process( const bar_type& b )
				{
					if ( b.index == 3 )
						register_signal( b, -43 );
					if ( b.index == 18 )
						register_signal( b, 98 );
				}
				//
				on_period_test_algorithm::on_period_test_algorithm( const algorithm_init& init )
					: typed_algorithm( init, typed_serie_ptr( new bool_vector_serie() ) )
				{
				}
				on_period_test_algorithm::~on_period_test_algorithm()
				{
				}
				void on_period_test_algorithm::process( const bar_type& b )
				{
					if ( b.index == 3 )
						register_signal( b, true );
					if ( b.index == 18 )
						register_signal( b, true );
				}
			}
			algorithm_manager_helper::algorithm_manager_helper()
				: algorithm_manager( stock_names )
			{
			}
			algorithm_manager_helper::~algorithm_manager_helper()
			{
			}
		}
	}
}
