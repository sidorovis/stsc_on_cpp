#include <algorithm_manager.h>

namespace stsc
{
	namespace engine
	{
		algorithm_manager::algorithm_manager( const shared_name_storage& stock_names )
			: stock_names_( stock_names )
		{
		}
		algorithm_manager::~algorithm_manager()
		{
		}
	}
}
