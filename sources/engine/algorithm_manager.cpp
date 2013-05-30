#include <algorithm_manager.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			executions_stock_group::executions_stock_group()
			{
			}
			executions_stock_group::~executions_stock_group()
			{
			}
			void executions_stock_group::clear()
			{
				on_period_algorithms_.clear();
				on_bar_algorithms_.clear();
				on_stock_algorithms_.clear();
			}
		}
		//
		algorithm_manager::algorithm_manager()
		{
		}
		algorithm_manager::~algorithm_manager()
		{
		}
		
		void algorithm_manager::clear()
		{
			data_processors_.clear();
		}
	}
}
