#ifndef _STSC_TESTS_ENGINE_ALGORITHM_EXAMPLES_H_
#define _STSC_TESTS_ENGINE_ALGORITHM_EXAMPLES_H_

#include <algorithms_storage/on_stock_algorithm.h>
#include <algorithms_storage/on_bar_algorithm.h>
#include <algorithms_storage/on_period_algorithm.h>

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
				namespace
				{
					typedef stsc::engine::algorithms_storage::on_stock_algorithm< double > on_stock_double;
					typedef stsc::engine::series_storage::map_serie< double > double_map_serie;

					typedef stsc::engine::algorithms_storage::on_bar_algorithm< int > on_bar_int;
					typedef stsc::engine::series_storage::map_serie< int > int_map_serie;

					typedef stsc::engine::algorithms_storage::on_period_algorithm< bool > on_period_bool;
					typedef stsc::engine::series_storage::vector_serie< bool > bool_vector_serie;


					typedef stsc::engine::algorithms_storage::details::algorithm_init algorithm_init;
					typedef stsc::engine::algorithms_storage::on_stock_algorithm_init< int > on_stock_algorithm_init;
				}
				class on_stock_test_algorithm : public on_stock_double
				{
					typedef on_stock_double typed_algorithm;
				public:
					explicit on_stock_test_algorithm( const on_stock_algorithm_init& init );
					virtual ~on_stock_test_algorithm();
					/// just for test purpose next methods are public, please use private for real algorithms
					virtual void process( const bar_type& b ); 
				};
				//
				class on_bar_test_algorithm : public on_bar_int
				{
					typedef on_bar_int typed_algorithm;
				public:
					explicit on_bar_test_algorithm( const algorithm_init& init );
					virtual ~on_bar_test_algorithm();
					/// just for test purpose next methods are public, please use private for real algorithms
					virtual void process( const bar_type& b ); 
				};			
				//
				class on_period_test_algorithm : public on_period_bool
				{
					typedef on_period_bool typed_algorithm;
				public:
					explicit on_period_test_algorithm( const algorithm_init& init );
					virtual ~on_period_test_algorithm();
					/// just for test purpose next methods are public, please use private for real algorithms
					virtual void process( const bar_type& b ); 
				};
			}
			struct algorithm_manager_helper : public stsc::engine::algorithm_manager
			{
				common::shared_name_storage stock_names;
				explicit algorithm_manager_helper();
				~algorithm_manager_helper();
			};
		}
	}
}

#endif // _STSC_TESTS_ALGORITHM_STORAGE_ALGORITHM_EXAMPLES_H_

