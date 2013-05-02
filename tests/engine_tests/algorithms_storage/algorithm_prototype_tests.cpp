#include <test_registrator.h>

#include <vector>

#include <algorithms_storage/algorithm_prototype.h>

#include <algorithm_examples.h>

using namespace stsc::engine::algorithms_storage;
using namespace stsc::engine;

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
					class algorithm_prototype_tests : public details::algorithm_prototype< common::on_period, double >
					{

						typedef details::algorithm_prototype< common::on_period, double > typed_algorithm;

					public:
						std::vector< double > signals_;

						typedef typed_algorithm::signal_type_ptr signal_type_ptr;

						explicit algorithm_prototype_tests( const details::algorithm_init& init )
							: typed_algorithm( init )
						{}
						virtual ~algorithm_prototype_tests(){}
						//
						virtual void register_signal( const bar_type& b, const signal_type_ptr& signal )
						{
							return signals_.push_back( *signal );
						}
						virtual void register_signal( const bar_type& b, const signal_type& signal )
						{
							return typed_algorithm::register_signal( b, signal );
						}
						virtual void register_signal( const bar_type& b, signal_type* const signal )
						{
							return typed_algorithm::register_signal( b, signal );
						}
						virtual typed_serie_ptr serie_prototype() const
						{
							return stsc::engine::series_storage::serie_ptr< signal_type >();
						}
					};
				}
				void details_algorithm_prototypes_constructor_tests()
				{
					algorithm_manager_helper algorithm_manager;
					algorithm_prototype_tests apt( details::algorithm_init( "name", algorithm_manager ) );

					common::on_period bar;

					apt.register_signal( bar, 4.5 );
					apt.register_signal( bar, new double( 5.5 ) );
					apt.register_signal( bar, algorithm_prototype_tests::signal_type_ptr( new double( 6.5 ) ) );
					BOOST_CHECK_EQUAL( apt.signals_.size(), 3ul );
					BOOST_CHECK_EQUAL( apt.signals_[0], 4.5 );
					BOOST_CHECK_EQUAL( apt.signals_[1], 5.5 );
					BOOST_CHECK_EQUAL( apt.signals_[2], 6.5 );
				}
			}
		}
	}
}

