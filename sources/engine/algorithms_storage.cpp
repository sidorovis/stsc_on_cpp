#include <algorithms_storage.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			void algorithm_storage::insert( const_pointer algo )
			{
				data_.insert( std::make_pair( algo->name_, algo ) );
			}
			void algorithm_storage::erase( const_pointer algo )
			{
				data_.erase( algo->name_ );
			}
			//
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
