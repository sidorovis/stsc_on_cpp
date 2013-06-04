#include <test_registrator.h>

#include <vector>

#include <algorithms_storage/algorithm_prototype.h>

#include <algorithm_examples.h>

using namespace stsc::engine::algorithms_storage;
using namespace stsc::engine::series_storage;

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
					class algorithm_prototype_tests : public algorithm_prototype< common::on_period, double >
					{

						typedef algorithm_prototype< common::on_period, double > typed_algorithm;

					public:
						std::vector< double > signals_;

						typedef typed_algorithm::signal_type_ptr signal_type_ptr;

						algorithm_prototype_tests( const algorithm_prototype_tests& other )
							: typed_algorithm( other )
						{}

						explicit algorithm_prototype_tests( const common::shared_string& name )
							: typed_algorithm( name, create_map_serie_ptr< double >() )
						{}
						virtual ~algorithm_prototype_tests(){}
						//
						virtual void register_signal( const bar_type& b, const signal_type_ptr& signal )
						{
							return signals_.push_back( *signal );
						}
						virtual algorithm* copy() const
						{
							return new algorithm_prototype_tests( *this );
						}
						virtual void register_signal( const bar_type& b, const signal_type& signal )
						{
							return typed_algorithm::register_signal( b, signal );
						}
						virtual void register_signal( const bar_type& b, signal_type* const signal )
						{
							return typed_algorithm::register_signal( b, signal );
						}
					};
				}
				void details_algorithm_prototypes_constructor_tests()
				{
					common::shared_string name( new std::string( "name" ) );
					algorithm_prototype_tests apt( name );

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

