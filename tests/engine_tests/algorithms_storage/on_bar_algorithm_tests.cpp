#include <test_registrator.h>

#include <vector>

#include <common/bar_types.h>

#include <algorithm_examples.h>

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
					using namespace stsc::engine::algorithms_storage;
					using namespace stsc::engine;

					create_algorithm< on_bar_test_algorithm >( "bar_test_algo" );
					
					typed_algorithm< on_bar_test_algorithm > algo = algorithm_storage().create_on_bar< on_bar_test_algorithm >( "bar_test_algo" );

					common::price_bar pb;
					pb.close_ = 14.5;
					common::on_bar b1( pb, 1 );
					BOOST_CHECK_NO_THROW( algo->process( b1 ) );

					pb.close_ = 14.5;
					common::on_bar b2( pb, 3 );
					BOOST_CHECK_NO_THROW( algo->process( b2 ) );

					pb.close_ = 14.5;
					common::on_bar b3( pb, 18 );
					BOOST_CHECK_NO_THROW( algo->process( b3 ) );

					algorithm_storage().clear();
				}
			}
		}
	}
}
