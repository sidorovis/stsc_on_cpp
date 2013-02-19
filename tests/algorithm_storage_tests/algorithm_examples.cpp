#include <algorithm_examples.h>

#include <strategies_engine.h>

namespace stsc
{
	namespace tests_
	{
		namespace algorithm_storage
		{
			double_out_algorithm::double_out_algorithm( const std::string& name, strategies_engine& es )
					: algorithm_prototype< double >( name, es )
			{
			}
			double_out_algorithm::~double_out_algorithm()
			{
			}
			void double_out_algorithm::process( const common::bar_type& b )
			{
				registrate_signal( b, new double( 1.5 ) );
			}
			void_out_algorithm::void_out_algorithm( const std::string& name, strategies_engine& es, const std::string& doa_algo_name )
				: algorithm_prototype< void >( name, es )
				, double_out_serie_( es.subscribe< double >( doa_algo_name ) )
			{
			}
			void_out_algorithm::~void_out_algorithm()
			{
			}
			void void_out_algorithm::process( const common::bar_type& b )
			{
				double_serie::pointer p = double_out_serie_.at( b );
				if ( p )
				{
					std::cout << *p << std::endl;
				}
			}
		}
	}
}