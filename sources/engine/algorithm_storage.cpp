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
			//
			common::shared_string algorithm_storage_instance::register_algorithm_name( const std::string& algorithm_name )
			{
				algorithm_names_.add_name( algorithm_name );
				common::shared_string result = algorithm_names_.get_shared( algorithm_name );
				return result;
			}
			//

		}
		//
		details::algorithm_storage_instance& algorithm_storage()
		{
			static details::algorithm_storage_instance instance;
			return instance;
		}
	}
}
