#include <algorithm_examples.h>

#include <strategies_engine.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			on_stock_algorithm_example::on_stock_algorithm_example( const std::string& name, stsc::engine::strategies_engine& es )
				: on_stock_algorithm_prototype< double >( name, es )
			{
			}
			on_stock_algorithm_example::~on_stock_algorithm_example()
			{
			}
			void on_stock_algorithm_example::process( const stsc::common::price_bar& b )
			{
			}
			//
			on_bar_algorithm_example::on_bar_algorithm_example( const std::string& name, stsc::engine::strategies_engine& se, const std::string& subscription_name )
				: on_bar_algorithm_prototype< int >( name, se )
				, double_serie_(  subscribe< double >( subscription_name ) )
			{
			}
			on_bar_algorithm_example::~on_bar_algorithm_example()
			{
			}
			void on_bar_algorithm_example::process( const stsc::common::bar_type& b )
			{
			}
			//
			on_period_algorithm_example::on_period_algorithm_example( 
				const std::string& name, 
				stsc::engine::strategies_engine& se, 
				const std::string& double_subscription_name,
				const std::string& int_subscription_name )
				 : on_period_algorithm_prototype< stsc::common::signal >( name, se )
				 , double_serie_( subscribe< double >( double_subscription_name ) )
				 , int_serie_( subscribe< int >( int_subscription_name ) )
			{
			}
			on_period_algorithm_example::~on_period_algorithm_example()
			{
			}
			void on_period_algorithm_example::process( const stsc::common::bar_type& b )
			{
			}
		}
	}
}