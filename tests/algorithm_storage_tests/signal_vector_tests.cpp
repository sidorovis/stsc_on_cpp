#include <test_registrator.h>

#include <signal_vector.h>

using namespace stsc::algorithm_storage;

namespace stsc
{
	namespace tests_
	{
		namespace algorithm_storage
		{
			void signal_vector_unit_tests()
			{
				class signal_vector_test_class : public signal_vector< double >
				{
				};

				signal_vector_test_class svtc;

				common::bar_type b1;
				BOOST_CHECK_NO_THROW( svtc.insert( b1, new double( 1.5 ) ) );
				common::bar_type b2;
				BOOST_CHECK_NO_THROW( svtc.insert( b2, new double( 1.3 ) ) );
				{
					boost::shared_ptr< double > throw_double( new double( 1.3 ) );
					BOOST_CHECK_THROW( svtc.insert( b2, throw_double.get() ), std::exception );
				}

				const double* e = svtc.at( b2 );
				BOOST_CHECK_EQUAL( *e, 1.3 );
				BOOST_CHECK_EQUAL( *svtc.at( b1 ), 1.5 );
				BOOST_CHECK_NO_THROW( svtc.clear() );
				BOOST_CHECK_NO_THROW( svtc.at( b1 ) );
				BOOST_CHECK_EQUAL( svtc.at( b1 ) == NULL, true );
			}
		}
	}
}

