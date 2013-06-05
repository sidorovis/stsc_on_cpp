#include <test_registrator.h>

#include <vector>

#include <algorithms/moving_median_series.h>

#include <algorithm_examples.h>

using namespace stsc::engine::algorithms;
using namespace stsc::engine::algorithms_storage;
using namespace stsc::engine::details;
using namespace stsc::engine;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms
			{
				class moving_median_series_test_helper : public moving_median_series
				{
				public:
					explicit moving_median_series_test_helper()
						: moving_median_series( "mov med test name" )
					{
					}
					virtual ~moving_median_series_test_helper(){}
					//
					virtual void process( const bar_type& b )
					{
						return moving_median_series::process( b );
					}
					generate_copy_method( moving_median_series_test_helper )
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
						typedef moving_median_series_test_helper mm_close;

						BOOST_CHECK_NO_THROW( create_algorithm< mm_close >() );
						BOOST_CHECK_NO_THROW( algorithm_storage().clear() );
					}
					void simple_work_tests()
					{
						execution_ptr exe( make_execution( "name", execution::STOCK, "moving median" ) );
						exe->add_parameter( "window_size", 3 );

						create_algorithm< moving_median_series_test_helper >();

						typed_algorithm< moving_median_series_test_helper > mms = algorithm_storage().create_on_stock< moving_median_series_test_helper >( "mov med test name" );

						mms->initialization( exe );

						for ( long i = 1; i < 1000; ++i )
						{
							common::price_bar pb;
							pb.close_ = i * 1.0f;
							pb.time_ = i;
							common::on_stock_bar bar( pb, i );
							BOOST_CHECK_NO_THROW( mms->process( bar ) );
						}
						BOOST_CHECK_NO_THROW( algorithm_storage().clear() );
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
