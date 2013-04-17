#include <test_registrator.h>

#include <vector>

#include <algorithms/moving_median_series.h>

using namespace stsc::engine::algorithms;

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
					explicit moving_median_series_test_helper( const std::string& name, const size_t window )
						: moving_median_series<>( name, window )
					{
					}
					virtual ~moving_median_series_test_helper(){}
					virtual void process( const bar_type& b )
					{
///						moving_median_series<>::process( b ); TODO finish this test!!!!
					}
				};
				class moving_median_series_tests
				{
					typedef moving_median_series<> moving_median_series_type;
					typedef boost::shared_ptr< moving_median_series_type > mms_ptr;

				public:
					explicit moving_median_series_tests()
					{
					}
					void constructor_tests()
					{
						BOOST_CHECK_NO_THROW( moving_median_series< stsc::common::bar_data_type::close > mmst( "test_moving_median_close", 3 ) );

						typedef moving_median_series< stsc::common::bar_data_type::open > mm_open;
						BOOST_CHECK_NO_THROW( mm_open mmo( "test_moving_median_open", 3 ) );
					}
					void simple_work_tests()
					{
						common::shared_string aapl[] = { common::shared_string( new std::string( "aapl" ) ) };
						moving_median_series_test_helper mms( "test_algorithm_name", 3 );

						mms.register_stock_list< common::shared_string* >( aapl + 0, aapl + 1 );

						for ( long i = 1; i < 1000; ++i )
						{
							common::price_bar pb;
							pb.close_ = i * 1.0f;
							pb.time_ = i;
							common::on_stock_bar bar( aapl[0], pb, i );
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
