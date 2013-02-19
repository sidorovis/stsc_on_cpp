#include <signal_vector.h>

namespace stsc
{
	namespace algorithm_storage
	{
		namespace
		{
			class signal_vector_instantiation_example : signal_vector< double >
			{
				signal_vector_instantiation_example()
					: signal_vector< double >()
				{
					common::bar_type b;
					insert( b, new double( 1.5 ) );
					clear();
				}
			};
		}
	}
}


