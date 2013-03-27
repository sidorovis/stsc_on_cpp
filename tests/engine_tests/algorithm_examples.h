#ifndef _STSC_TESTS_ENGINE_ALGORITHM_EXAMPLES_H_
#define _STSC_TESTS_ENGINE_ALGORITHM_EXAMPLES_H_

#include <bar_types.h>
#include <signal_types.h>

#include <on_stock_algorithm_prototype.h>
#include <on_period_algorithm_prototype.h>
#include <on_bar_algorithm_prototype.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			class on_stock_algorithm_example : public stsc::engine::on_stock_algorithm_prototype< double >
			{
			public:
				explicit on_stock_algorithm_example( const std::string& name, stsc::engine::strategies_engine& es );
				virtual ~on_stock_algorithm_example();
			private:
				virtual void process( const stsc::common::price_bar& b );
			};
			//
			class on_bar_algorithm_example : public stsc::engine::on_bar_algorithm_prototype< int >
			{
				stsc::engine::signal_vector< double > double_serie_;
			public:
				explicit on_bar_algorithm_example( const std::string& name, stsc::engine::strategies_engine& es, const std::string& subscription_name );
				virtual ~on_bar_algorithm_example();
			private:
				virtual void process( const stsc::common::bar_type& b );
			};
			class on_period_algorithm_example : public stsc::engine::on_period_algorithm_prototype< stsc::common::signal >
			{
				stsc::engine::signal_vector< double > double_serie_;
				stsc::engine::signal_vector< int > int_serie_;
			public:
				explicit on_period_algorithm_example( 
					const std::string& name, 
					stsc::engine::strategies_engine& es, 
					const std::string& double_subscription_name,
					const std::string& int_subscription_name );
				virtual ~on_period_algorithm_example();
			private:
				virtual void process( const stsc::common::bar_type& b );
			};			
		}
	}
}


#endif // _STSC_TESTS_ALGORITHM_STORAGE_ALGORITHM_EXAMPLES_H_

