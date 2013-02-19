#include <strategies_engine.h>

#include <algorithms/algorithm_prototype.h>

namespace stsc
{
	namespace algorithm_storage
	{
		strategies_engine::strategies_engine()
		{
		}
		strategies_engine::~strategies_engine()
		{
			clear();
		}
		void strategies_engine::clear()
		{
			algorithms_.clear();
		};
	}
}

