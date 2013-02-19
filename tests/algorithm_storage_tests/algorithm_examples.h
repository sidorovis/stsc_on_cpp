#ifndef _STSC_TESTS_ALGORITHM_STORAGE_ALGORITHM_EXAMPLES_H_
#define _STSC_TESTS_ALGORITHM_STORAGE_ALGORITHM_EXAMPLES_H_

#include <algorithms/algorithm_prototype.h>

using namespace stsc::algorithm_storage;

namespace stsc
{
	namespace tests_
	{
		namespace algorithm_storage
		{
			class double_out_algorithm : public algorithm_prototype< double >
			{
			public:
				explicit double_out_algorithm( const std::string& name, strategies_engine& es );
				virtual ~double_out_algorithm();
			private:
				virtual void process( const common::bar_type& b );
			};
			class void_out_algorithm : public algorithm_prototype< void >
			{
				typedef signal_vector< double > double_serie;
				const double_serie double_out_serie_;
			public:
				explicit void_out_algorithm( const std::string& name, strategies_engine& es, const std::string& doa_algo_name );
				virtual ~void_out_algorithm();
			private:
				virtual void process( const common::bar_type& b );
			};
		}
	}
}


#endif // _STSC_TESTS_ALGORITHM_STORAGE_ALGORITHM_EXAMPLES_H_

