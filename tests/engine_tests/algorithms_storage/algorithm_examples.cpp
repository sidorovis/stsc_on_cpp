#include <algorithms_storage/algorithm_examples.h>

#include <series_storage/map_serie.h>
#include <series_storage/vector_serie.h>

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
				on_stock_test_algorithm::serie_ptr on_stock_test_algorithm::serie_prototype() const
				{
					return serie_ptr( new stsc::engine::series_storage::map_serie< signal_type >() );
				}
				//
				on_bar_test_algorithm::on_bar_test_algorithm( const std::string& name )
					: typed_algorithm( name )
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
				void on_bar_test_algorithm::register_serie()
				{
					return typed_algorithm::register_serie();
				}
				on_bar_test_algorithm::serie_ptr on_bar_test_algorithm::serie_prototype() const
				{
					return serie_ptr( new stsc::engine::series_storage::vector_serie< signal_type >() );
				}
				//
				on_period_test_algorithm::on_period_test_algorithm( const std::string& name )
					: typed_algorithm( name )
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
				void on_period_test_algorithm::register_serie()
				{
					return typed_algorithm::register_serie();
				}
				on_period_test_algorithm::serie_ptr on_period_test_algorithm::serie_prototype() const
				{
					return serie_ptr( new stsc::engine::series_storage::map_serie< signal_type >() );
				}
			}
		}
	}
}
