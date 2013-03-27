#include "test_registrator.h"

#include <vector>

#include <algorithms/moving_median_series.h>

#include <strategies_engine.h>

using namespace stsc::engine;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			class moving_median_series_tests
			{
				typedef moving_median_series<> moving_median_series_type;
				typedef boost::shared_ptr< moving_median_series_type > mms_ptr;
				typedef boost::shared_ptr< strategies_engine > strategies_engine_ptr;
				strategies_engine_ptr se_;

			public:
				explicit moving_median_series_tests()
				{
					se_.reset( new strategies_engine() );
				}
				void constructor_tests()
				{
					{
						mms_ptr mms;
						BOOST_CHECK_NO_THROW( mms.reset( new moving_median_series_type( "test_moving_median_close", *se_, 3 ) ) );
					}
					{
						boost::shared_ptr< moving_median_series< stsc::common::bar_data_type::open > > test_mms_open;
						BOOST_CHECK_NO_THROW( test_mms_open.reset( new moving_median_series< stsc::common::bar_data_type::open >( "test_moving_median_open", *se_, 3 ) ) );
					}
				}
				void simple_work_tests()
				{
					mms_ptr mms;
					BOOST_CHECK_NO_THROW( mms.reset( new moving_median_series_type( "test_moving_median_close", *se_, 3 ) ) );
					typedef boost::shared_ptr< common::price_bar > bad_ptr;
					std::vector< bad_ptr > pb_vector;
					for ( int i = 1; i < 1000; ++i )
					{
						bad_ptr pb( new common::price_bar );
						pb->close_ = common::price_bar::float_type( i );
						pb->time_ = long( i );
						pb_vector.push_back( pb );
						BOOST_CHECK_NO_THROW( mms->process( *pb ) );
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
