#include <signals_storage.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			signals_storage::~signals_storage()
			{
				for( vectors::iterator i = data_.begin() ; i != data_.end() ; ++i )
					delete i->second;
			}
			void signals_storage::destroy_vector( const std::string& name )
			{
				vectors::iterator i = data_.find( name );
				if ( i == data_.end() )
					return;
				delete i->second;
				data_.erase( i );
			}
			std::ostream& operator<<( std::ostream& out, const signals_storage& ss )
			{
				out << "signal_vectors: ";
				for ( signals_storage::vectors::const_iterator i = ss.data_.begin() ; i != ss.data_.end() ; ++i )
					out << "'" << i->first << "' ";
				return out;
			}
		}
	}
}