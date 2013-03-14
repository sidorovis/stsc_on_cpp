#include "test_registrator.h"

#include <vector>

#include <algorithms/moving_median_indicator.h>

#include <strategies_engine.h>

using namespace stsc::engine;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			class moving_median_indicator_tests
			{
				typedef boost::shared_ptr< moving_median_indicator > mmi_ptr;
				typedef boost::shared_ptr< strategies_engine > strategies_engine_ptr;
				strategies_engine_ptr se_;

			public:
				explicit moving_median_indicator_tests()
				{
					se_.reset( new strategies_engine() );
				}
				void constructor_tests()
				{
					mmi_ptr mmi;
					BOOST_CHECK_NO_THROW( mmi.reset( new moving_median_indicator( "good_mm", *se_, 3, 10.0, 20.0 ) ) );
					BOOST_CHECK_EQUAL( mmi->bigger_than_, 10.0 );
					BOOST_CHECK_EQUAL( mmi->less_than_, 20.0 );
					BOOST_CHECK_EQUAL( mmi->mm_.get() != NULL, true );
					BOOST_CHECK_THROW( mmi.reset( new moving_median_indicator( "bad1_mm", *se_, 3, 20.0, 10.0 ) ), std::invalid_argument );
					BOOST_CHECK_THROW( mmi.reset( new moving_median_indicator( "bad2_mm", *se_, 3, 10.0, 10.0 ) ), std::invalid_argument );
				}
				void simple_work_tests()
				{
					mmi_ptr mmi;
					BOOST_CHECK_NO_THROW( mmi.reset( new moving_median_indicator( "good_mm", *se_, 3, 0.0, 2.0 ) ) );
					typedef boost::shared_ptr< common::price_bar > bad_ptr;
					std::vector< bad_ptr > pb_vector;
					for ( int i = 5; i < 1000; ++i )
					{
						bad_ptr pb( new common::price_bar );
						pb->close_ = common::price_bar::float_type( i );
						pb->time_ = long( i );
						pb_vector.push_back( pb );
						BOOST_CHECK_NO_THROW( mmi->process( *pb ) );
					}
				}
			};
			void moving_median_indicator_constructor_tests()
			{
				moving_median_indicator_tests mmi_test;
				mmi_test.constructor_tests();
			}
			void moving_median_indicator_simple_work_tests()
			{
				moving_median_indicator_tests mmi_test;
				mmi_test.simple_work_tests();
			}
		}
	}
}
