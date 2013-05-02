#include <test_registrator.h>

#include <vector>

#include <algorithms/moving_median_series.h>
#include <algorithms/moving_median_indicator.h>

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

				class moving_median_indicator_tests
				{
					typedef boost::shared_ptr< moving_median_series<> > mms_ptr;
					typedef boost::shared_ptr< moving_median_indicator > mmi_ptr;
					typedef boost::shared_ptr< stsc::engine::algorithm_manager > algorithm_manager_ptr;

					algorithm_manager_ptr am_;

				public:
					explicit moving_median_indicator_tests()
					{
						am_.reset( new stsc::engine::algorithm_manager() );
					}
					void constructor_tests()
					{
						typedef moving_median_indicator_init_data mmiid;
						typedef moving_median_indicator::init_type mmiinit;
						mmiinit mmi_init( common::make_shared_string( "mmi" ), *am_, mmiid( "moving_median_close", 10.0, 20.0 ) );
						moving_median_series_init mms_init( common::make_shared_string( "moving_median_close" ), *am_ );
						mmi_ptr mmi;

						BOOST_CHECK_THROW( new moving_median_indicator( mmi_init ), std::logic_error );
						mms_ptr mms;
						BOOST_CHECK_NO_THROW( mms.reset( new moving_median_series<>( mms_init ) ) );
						BOOST_CHECK_NO_THROW( mmi.reset( new moving_median_indicator( mmi_init ) ) );
						BOOST_CHECK_EQUAL( mmi->bigger_than_, 10.0 );
						BOOST_CHECK_EQUAL( mmi->less_than_, 20.0 );
						BOOST_CHECK_THROW( new moving_median_indicator( mmi_init ), std::logic_error );
						BOOST_CHECK_THROW( new moving_median_indicator( mmi_init ), std::invalid_argument );
						BOOST_CHECK_THROW( new moving_median_indicator( mmi_init ), std::invalid_argument );
					}
					void simple_work_tests()
					{
						typedef moving_median_indicator_init_data mmiid;
						typedef moving_median_indicator::init_type mmiinit;
						mmiinit mmi_init( common::make_shared_string( "mmi" ), *am_, mmiid( "moving_median_close", 10.0, 20.0 ) );
						moving_median_series_init mms_init( common::make_shared_string( "moving_median_close" ), *am_ );

						mmi_ptr mmi;
						mms_ptr mms;
						BOOST_CHECK_NO_THROW( mms.reset( new moving_median_series<>( mms_init ) ) );
						BOOST_CHECK_NO_THROW( mmi.reset( new moving_median_indicator( mmi_init ) ) );

						typedef boost::shared_ptr< common::price_bar > bar_ptr;
						std::vector< bar_ptr > pb_vector;

						for ( size_t i = 1; i < 1000; ++i )
						{
							bar_ptr pb( new common::price_bar );
							pb->close_ = common::price_bar::float_type( i );
							pb->time_ = long( i );
							pb_vector.push_back( pb );

							common::on_stock_bar osb( *pb, i );

							BOOST_CHECK_NO_THROW( mms->process( osb ) );
							BOOST_CHECK_NO_THROW( mmi->process( osb ) );
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
}
