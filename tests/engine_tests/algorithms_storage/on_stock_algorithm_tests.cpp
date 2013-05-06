#include <test_registrator.h>

#include <vector>

#include <common/bar_types.h>

#include <algorithms_storage/on_stock_algorithm.h>
#include <algorithm_examples.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms_storage
			{
				void on_stock_algorithm_tests()
				{
					using namespace stsc::engine::algorithms_storage;
					using namespace stsc::common;

					algorithm_manager_helper algorithm_manager;
					on_stock_test_algorithm algo( on_stock_algorithm_init( make_shared_string( "the_name" ), algorithm_manager ) );

					price_bar pb;
					pb.close_ = 14.5;
					on_stock_bar b1( pb, 1 );

					BOOST_CHECK_NO_THROW( algo.process( b1 ) );

					on_stock_bar b2( pb, 2 );
					pb.close_ = 0.56f;
					BOOST_CHECK_NO_THROW( algo.process( b2 ) );
					
					on_stock_bar b2_c( pb, 2 );
					BOOST_CHECK_THROW( algo.process( b2_c ), std::exception );

					on_stock_bar b3( pb, 3 );
					pb.close_ = 5.27f;
					BOOST_CHECK_NO_THROW( algo.process( b3 ) );
				}
			}
		}
	}
}
