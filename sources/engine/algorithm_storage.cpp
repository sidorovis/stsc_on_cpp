#include <algorithm_storage.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{

			algorithm_storage_instance::algorithm_storage_instance()
			{
			}
			algorithm_storage_instance::~algorithm_storage_instance()
			{
			}
		}
		//
		details::algorithm_storage_instance& algorithm_storage()
		{
			static details::algorithm_storage_instance instance;
			return instance;
		}
	}
}
