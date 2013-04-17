#include <test_registrator.h>

#include <algorithms/moving_median.h>

using namespace stsc::engine::algorithms::details;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms
			{
				class details_moving_median_tests
				{
				public:
					static void constructor_tests()
					{
						{
							moving_median< double > median( 3 );
							BOOST_CHECK_EQUAL( sizeof( moving_median<double>::median_set ), sizeof( std::multiset< double > ) );
							BOOST_CHECK_EQUAL( sizeof( moving_median<double>::real_values ), sizeof( std::deque< double > ) );
							BOOST_CHECK_EQUAL( sizeof( median.window_ ), sizeof( size_t ) );
						}
						{
							moving_median< int > median( 3 );
							BOOST_CHECK_EQUAL( sizeof( moving_median<int>::median_set ), sizeof( std::multiset< int > ) );
							BOOST_CHECK_EQUAL( sizeof( moving_median<int>::real_values ), sizeof( std::deque< int > ) );
							BOOST_CHECK_EQUAL( sizeof( median.window_ ), sizeof( size_t ) );
						}
						{
							BOOST_CHECK_THROW( moving_median< double > median( 1 ), std::invalid_argument );
						}
						{
							moving_median< double > median( 4 );
							BOOST_CHECK_EQUAL( median.window_, 5 );
						}
					}
					static void simple_work_tests()
					{	
						const int lowest=-10, highest=10;
						const int range = ( highest-lowest ) + 1;
						int cents = lowest + int( range * rand() / ( RAND_MAX + 1.0 ) );

						{
							typedef double number_type;
							const size_t window = 5;
							moving_median<number_type> median( window );
							BOOST_CHECK_THROW( median.get_median(), std::logic_error );

							const number_type value = 16;
							
							for ( int i = 0; i < 100; ++i)
							{		
								cents = lowest + int( range * rand() / ( RAND_MAX + 1.0 ) );
									
								const number_type value_to_add = ( i % 3 == 0 ) ? value + (double)cents / 100 : value;								
								median.add_element( value_to_add );
									
								if ( i < window - 1 )
								{
									BOOST_CHECK_EQUAL( median.get_median(), value_to_add );
								} else
								{
									BOOST_CHECK_EQUAL( median.get_median(), value );
								}
							}
						}
						{
							typedef double number_type;

							const size_t window = 19;
							moving_median< number_type> median( window );	
							BOOST_CHECK_THROW( median.get_median(), std::logic_error );

							const number_type value = 16;			
							const double cents = 0.01;
							for ( int i = 0; i < 100; ++i)
							{							
								const number_type value_to_add = ( i % 2 == 0 ) ? value + (double)cents / 100 : value;								
								median.add_element( value_to_add );								
								if ( i < window - 1 )
								{
									BOOST_CHECK_EQUAL( median.get_median(), value_to_add );
								}
								else
								{
									BOOST_CHECK_EQUAL( median.get_median(), value_to_add );
								}
							}
						}
						{ /// simple adding the same value						
							moving_median< double > median( 5 );
							for ( size_t i = 0 ; i < 1000 ; ++i )
								BOOST_CHECK_NO_THROW( median.add_element( 0.9999999990621 ) );
						}
					}
				};
				void details_moving_median_constructor_tests()
				{
					details_moving_median_tests::constructor_tests();
				}
				void details_moving_median_simple_work_tests()
				{
					details_moving_median_tests::simple_work_tests();
				}
			}
		}
	}
}
