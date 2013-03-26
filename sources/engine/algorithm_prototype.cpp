#include <algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace
		{
			void serialization_testing_method()
			{
				class on_stock_algorithm_prototype_serialization_test : on_stock_algorithm_prototype< int > 
				{
				public:
					explicit on_stock_algorithm_prototype_serialization_test( const std::string& name, strategies_engine& se )
						: on_stock_algorithm_prototype( name, se )
					{
					}
					virtual ~on_stock_algorithm_prototype_serialization_test()
					{
					}
					virtual void process( const bar_type& b )
					{
					}
				};
				//
				strategies_engine se;
				on_stock_algorithm_prototype_serialization_test working( "serialization successfull", se );
			}
		}
	}
}

