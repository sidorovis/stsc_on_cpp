#include <test_registrator.h>

#include <vector>

#include <bar_types.h>

#include <algorithms_storage/algorithm_examples.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms_storage
			{
				void on_bar_algorithm_tests()
				{
					on_bar_test_algorithm algo( "test_algo" );
					algo.register_serie();
					
					common::price_bar pb;
					pb.close_ = 14.5;
					common::on_bar b1( pb, 1 );
					BOOST_CHECK_NO_THROW( algo.process( b1 ) );

					pb.close_ = 14.5;
					common::on_bar b2( pb, 3 );
					BOOST_CHECK_NO_THROW( algo.process( b2 ) );

					pb.close_ = 14.5;
					common::on_bar b3( pb, 18 );
					BOOST_CHECK_NO_THROW( algo.process( b3 ) );
				}
			}
		}
	}
}
