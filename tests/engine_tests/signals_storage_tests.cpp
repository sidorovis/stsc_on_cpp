#include <test_registrator.h>

#include <signals_storage.h>

using namespace stsc::engine;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			void details_signals_storage_unit_tests()
			{
				details::signals_storage ss;
				BOOST_CHECK_NO_THROW( ss.create_vector< double >( "test creating vector, test auto delete on destructor" ) );
				signal_vector<double> sv1 = ss.create_vector< double >( "sv1" );
				signal_vector<double> sv1_copy = ss.subscribe< double >( "sv1" );
				common::bar_type b;
				BOOST_CHECK_EQUAL( sv1.at( &b ) == NULL, true );
				sv1_copy.insert( &b, new double( 1.5 ) );
				BOOST_CHECK_EQUAL( *sv1.at( &b ), 1.5 );

				std::stringstream out;
				out << ss;
				BOOST_CHECK_EQUAL( out.str(), "signal_vectors: 'sv1' 'test creating vector, test auto delete on destructor' " );

				BOOST_CHECK_NO_THROW( ss.destroy_vector( "sv1" ) );
				BOOST_CHECK_NO_THROW( ss.destroy_vector( "sv1" ) );
				BOOST_CHECK_EQUAL( sv1.at( &b ) != NULL, true );
				BOOST_CHECK_EQUAL( *sv1.at( &b ), 1.5 );
				sv1.clear();
				BOOST_CHECK_EQUAL( sv1.at( &b ) == NULL, true );
			}
		}
	}
}