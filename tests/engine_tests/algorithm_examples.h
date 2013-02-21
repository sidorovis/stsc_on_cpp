#ifndef _STSC_TESTS_ENGINE_ALGORITHM_EXAMPLES_H_
#define _STSC_TESTS_ENGINE_ALGORITHM_EXAMPLES_H_

#include <algorithm_prototype.h>
#include <bar_types.h>

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
			class on_bar_algorithm_example : public stsc::engine::on_bar_algorithm_prototype< void >
			{
				stsc::engine::signal_vector< double > double_serie_;
			public:
				explicit on_bar_algorithm_example( const std::string& name, stsc::engine::strategies_engine& es, const std::string& subscription_name );
				virtual ~on_bar_algorithm_example();
			private:
				virtual void process( const stsc::common::bar_type& b );
			};
			//class void_out_algorithm : public stsc::engine::algorithm_prototype< common::bar_type, void >
			//{
			//	typedef stsc::engine::signal_vector< double > double_serie;
			//	const double_serie double_out_serie_;
			//public:
			//	explicit void_out_algorithm( const std::string& name, stsc::engine::strategies_engine& es, const std::string& doa_algo_name );
			//	virtual ~void_out_algorithm();
			//};
			//
			//class on_stock_algorithm_example : public stsc::engine::on_stock_algorithm_prototype< double >
			//{
			//	virtual void process( const stsc::common::price_bar& b )
			//	{
			//	}
			//};
			
		}
	}
}


#endif // _STSC_TESTS_ALGORITHM_STORAGE_ALGORITHM_EXAMPLES_H_

