#include <test_registrator.h>

#include <vector>

#include <algorithms_storage/algorithm_prototype.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace algorithms_storage
			{
				namespace
				{
					class algorithm_prototype_tests : public stsc::engine::algorithms_storage::details::algorithm_prototype< int, double >
					{
						typedef stsc::engine::algorithms_storage::details::algorithm_prototype< int, double > typed_algorithm;

					public:
						std::vector< double > signals_;

						typedef typed_algorithm::signal_type_ptr signal_type_ptr;

						explicit algorithm_prototype_tests()
							: typed_algorithm( "hello world tests" )
						{}
						~algorithm_prototype_tests(){}

						void register_signal( const bar_type& b, const signal_type& signal )
						{
							return typed_algorithm::register_signal( b, signal );
						}
						void register_signal( const bar_type& b, signal_type* const signal )
						{
							return typed_algorithm::register_signal( b, signal );
						}
						void register_signal( const bar_type& b, const signal_type_ptr& signal )
						{
							signals_.push_back( *signal );
						}
					};
				}
				void details_algorithm_prototypes_constructor_tests()
				{
					algorithm_prototype_tests apt;

					apt.register_signal( 1, 4.5 );
					apt.register_signal( 1, new double( 5.5 ) );
					apt.register_signal( 1, algorithm_prototype_tests::signal_type_ptr( new double( 6.5 ) ) );
					BOOST_CHECK_EQUAL( apt.signals_.size(), 3ul );
					BOOST_CHECK_EQUAL( apt.signals_[0], 4.5 );
					BOOST_CHECK_EQUAL( apt.signals_[1], 5.5 );
					BOOST_CHECK_EQUAL( apt.signals_[2], 6.5 );
				}
			}
		}
	}
}

