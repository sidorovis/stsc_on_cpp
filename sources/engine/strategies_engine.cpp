#include <strategies_engine.h>

#include <algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		strategies_engine::strategies_engine()
		{
		}
		strategies_engine::~strategies_engine()
		{
		}
		//
		void strategies_engine::registrate_on_stock_algorithm( details::algorithm_storage::const_pointer algorithm )
		{
			on_stock_algorithm_storage_.insert( algorithm );
		}
		void strategies_engine::unregister_on_stock_algorithm( details::algorithm_storage::const_pointer algorithm )
		{
			on_stock_algorithm_storage_.erase( algorithm );
		}
		//
		void strategies_engine::registrate_on_bar_algorithm( details::algorithm_storage::const_pointer algorithm )
		{
			on_bar_algorithm_storage_.insert( algorithm );
		}
		void strategies_engine::unregistrate_on_bar_algorithm( details::algorithm_storage::const_pointer algorithm )
		{
			on_bar_algorithm_storage_.erase( algorithm );
		}
		//
		void strategies_engine::registrate_on_period_algorithm( details::algorithm_storage::const_pointer algorithm )
		{
			on_period_algorithm_storage_.insert( algorithm );
		}
		void strategies_engine::unregistrate_on_period_algorithm( details::algorithm_storage::const_pointer algorithm )
		{
			on_period_algorithm_storage_.erase( algorithm );
		}
	}
}

