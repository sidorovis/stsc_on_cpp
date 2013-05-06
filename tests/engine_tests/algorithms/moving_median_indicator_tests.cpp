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

					common::shared_name_storage stock_names;
					algorithm_manager_ptr am_;

				public:
					explicit moving_median_indicator_tests()
					{
					}
					void add_stocks()
					{
						using stsc::engine::algorithm_manager;
						am_.reset( new algorithm_manager( stock_names ) );
						BOOST_CHECK_EQUAL( am_.get() != NULL, true );
						stock_names << "aapl" << "goog";
					}
					void constructor_tests()
					{
						using stsc::engine::algorithm_manager;

						typedef moving_median_indicator_init_data mmiid;
						add_stocks();

						typedef algorithm_manager::on_stock_algorithm_sequence algos_type;
						algos_type series, indicators;

						BOOST_CHECK_THROW( am_->create_on_stock_algorithm< moving_median_indicator >( "mmi", mmiid( "moving_median_close", 10.0, 20.0 ) ), std::logic_error );

						add_stocks();

						BOOST_CHECK_NO_THROW( series = (am_->create_on_stock_algorithm< moving_median_series<>, size_t >( "moving_median_close", 3 ) ) );
						BOOST_CHECK_NO_THROW( indicators = am_->create_on_stock_algorithm< moving_median_indicator >( "mmi", mmiid( "moving_median_close", 10.0, 20.0 ) ) );

						BOOST_CHECK_EQUAL( series.first != series.second, true );
						BOOST_CHECK_EQUAL( indicators.first != indicators.second, true );

						BOOST_CHECK_NO_THROW( indicators.first->second->subscription_check( typeid( common::open_signal ) ) );
						moving_median_indicator* mmi = dynamic_cast< moving_median_indicator* >( indicators.first->second.get() );

						BOOST_CHECK_EQUAL( mmi->bigger_than_, 10.0 );
						BOOST_CHECK_EQUAL( mmi->less_than_, 20.0 );
					}
					void simple_work_tests()
					{
						using stsc::engine::algorithm_manager;

						typedef moving_median_indicator_init_data mmiid;

						add_stocks();
						typedef algorithm_manager::on_stock_algorithm_sequence algos_type;
						algos_type series, indicators;
						BOOST_CHECK_NO_THROW( series = (am_->create_on_stock_algorithm< moving_median_series<>, size_t >( "moving_median_close", 3 ) ) );
						BOOST_CHECK_NO_THROW( indicators = am_->create_on_stock_algorithm< moving_median_indicator >( "mmi", mmiid( "moving_median_close", 10.0, 20.0 ) ) );

						BOOST_CHECK_EQUAL( series.first != series.second, true );
						BOOST_CHECK_EQUAL( indicators.first != indicators.second, true );

						BOOST_CHECK_NO_THROW( series.first->second->subscription_check( typeid( common::bar_data::float_type ) ) );
						BOOST_CHECK_NO_THROW( indicators.first->second->subscription_check( typeid( common::open_signal ) ) );

						moving_median_series<>* mms = dynamic_cast< moving_median_series<>* >( series.first->second.get() );
						moving_median_indicator* mmi = dynamic_cast< moving_median_indicator* >( indicators.first->second.get() );

						for ( size_t i = 1; i < 1000; ++i )
						{
							common::price_bar pb;
							pb.close_ = common::price_bar::float_type( i );
							pb.time_ = long( i );

							common::on_stock_bar osb( pb, i );
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
