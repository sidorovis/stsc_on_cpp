#ifndef _STSC_COMMON_TYPES_H_
#define _STSC_COMMON_TYPES_H_

#include <ostream>

#include <boost/shared_ptr.hpp>

#include <shared_name_storage.h>

namespace stsc
{
	namespace common
	{
		typedef size_t index;
		typedef system_utilities::common::shared_name_storage shared_name_storage;
		typedef system_utilities::common::shared_name_storage::shared_string shared_string;

		shared_string make_shared_string( const std::string& str );
	}
}

#endif // _STSC_COMMON_TYPES_H_