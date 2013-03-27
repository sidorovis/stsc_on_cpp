#ifndef _STSC_ENGINE_ALGORITHM_STORAGE_H_
#define _STSC_ENGINE_ALGORITHM_STORAGE_H_

#include <map>
#include <string>

#include <boost/noncopyable.hpp>

#include <algorithm.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			struct algorithm_storage
			{
				typedef algorithm* const const_pointer;
				typedef std::map< std::string, const_pointer > algorithms;
				algorithms data_;

				void insert( const_pointer algo );
				void erase( const_pointer algo );
			};
			std::ostream& operator<<( std::ostream& out, const algorithm_storage& as );
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHM_STORAGE_H_