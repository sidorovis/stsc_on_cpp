#include <test_registrator.h>

#include <vector>

#include <bar_types.h>

#include <algorithms_storage/on_stock_algorithm.h>
#include <algorithms_storage/algorithm_examples.h>

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
					std::vector< common::shared_string > stocks( 1ul );
					stocks[0].reset( new std::string( "aapl" ) );

					common::price_bar pb;
					pb.close_ = 14.5;
					common::on_stock_bar b1( stocks[0], pb, 1 );

					on_stock_test_algorithm algo( "name" );

					algo.register_stock_list( stocks.begin(), stocks.end() );

					BOOST_CHECK_NO_THROW( algo.process( b1 ) );

					common::on_stock_bar b2( stocks[0], pb, 2 );
					pb.close_ = 0.56f;
					BOOST_CHECK_NO_THROW( algo.process( b2 ) );
					common::on_stock_bar b2_c( stocks[0], pb, 2 );
					BOOST_CHECK_THROW( algo.process( b2_c ), std::exception );

					common::on_stock_bar b3( stocks[0], pb, 3 );
					pb.close_ = 5.27f;
					BOOST_CHECK_NO_THROW( algo.process( b3 ) );

					common::shared_string aapl_2( new std::string( "aapl" ) );
					common::on_stock_bar b4_not_real_stock_name( aapl_2, pb, 4 );
					BOOST_CHECK_THROW( algo.process( b4_not_real_stock_name ), std::exception );
				}
			}
		}
	}
}
