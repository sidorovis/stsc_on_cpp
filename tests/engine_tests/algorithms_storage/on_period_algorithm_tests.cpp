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
				void on_period_algorithm_tests()
				{
					using namespace stsc::engine::algorithms_storage;

 					algorithm_manager_helper algorithm_manager;

					on_period_test_algorithm algo( details::algorithm_init( "test_algo", algorithm_manager ) );
					
					common::bar_type bt;
					common::on_period b1( bt, 1 );
					BOOST_CHECK_NO_THROW( algo.process( b1 ) );

					common::on_period b2( bt, 3 );
					BOOST_CHECK_NO_THROW( algo.process( b2 ) );

					common::on_period b3( bt, 18 );
					BOOST_CHECK_NO_THROW( algo.process( b3 ) );
				}
			}
		}
	}
}
