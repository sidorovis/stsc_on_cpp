#include <test_registrator.h>

#include <vector>

#include <algorithms/moving_median_series.h>

#include <algorithm_examples.h>

using namespace stsc::engine::algorithms;
using namespace stsc::engine::algorithms_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms
			{
				class moving_median_series_test_helper : public moving_median_series<>
				{
				public:
					explicit moving_median_series_test_helper( const moving_median_series_init& init )
						: moving_median_series<>( init )
					{
					}
					virtual ~moving_median_series_test_helper(){}
					//
					virtual void process( const bar_type& b )
					{
						return moving_median_series<>::process( b );
					}
				};
				class moving_median_series_tests
				{
					typedef moving_median_series_test_helper moving_median_series_type;
					typedef boost::shared_ptr< moving_median_series_type > mms_ptr;

				public:
					explicit moving_median_series_tests()
					{
					}
					void constructor_tests()
					{
						typedef moving_median_series< stsc::common::bar_data_type::close > mm_close;
						algorithm_manager_helper subsman;

						moving_median_series_init osa_init( common::make_shared_string( "test_moving_median_close" ), subsman, 3 );

						BOOST_CHECK_NO_THROW( mm_close mmst( osa_init ) );

						typedef moving_median_series< stsc::common::bar_data_type::open > mm_open;
						BOOST_CHECK_NO_THROW( mm_open mmo( osa_init ) );
					}
					void simple_work_tests()
					{
						algorithm_manager_helper subsman;
						moving_median_series_init osa_init( common::make_shared_string( "test_moving_median_close" ), subsman, 3 );
						moving_median_series_test_helper mms( osa_init );

						for ( long i = 1; i < 1000; ++i )
						{
							common::price_bar pb;
							pb.close_ = i * 1.0f;
							pb.time_ = i;
							common::on_stock_bar bar( pb, i );
							BOOST_CHECK_NO_THROW( mms.process( bar ) );
						}
					}
				};
				void moving_median_series_constructor_tests()
				{
					moving_median_series_tests mms_test;
					mms_test.constructor_tests();
				}
				void moving_median_series_simple_work_tests()
				{
					moving_median_series_tests mms_test;
					mms_test.simple_work_tests();
				}
			}
		}
	}
}
