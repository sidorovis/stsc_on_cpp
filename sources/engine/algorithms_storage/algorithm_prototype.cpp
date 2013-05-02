#include <algorithms_storage/algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			namespace details
			{
				algorithm_init::algorithm_init( const common::shared_string& n, const algorithm_manager& m )
					: name( n )
					, manager( m )
				{
				}
				algorithm_init::algorithm_init( const std::string& n, const algorithm_manager& m )
					: name( common::make_shared_string( n ) )
					, manager( m )
				{
				}
			}
		}
	}
}
