#include <algorithm_storage.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			std::ostream& operator<<( std::ostream& out, const algorithm_storage& as )
			{
				out << "algorithms: ";
				for ( algorithm_storage::algorithms::const_iterator i = as.data_.begin() ; i != as.data_.end() ; ++i )
					out << i->first << " ";
				return out;
			}
		}
	}
}
