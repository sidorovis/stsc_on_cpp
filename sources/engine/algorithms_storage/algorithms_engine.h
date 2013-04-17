#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHMS_ENGINE_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHMS_ENGINE_H_

#include <map>

#include <boost/noncopyable.hpp>

#include <algorithms_storage/algorithm.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			class algorithms_engine : virtual public boost::noncopyable
			{
				typedef std::multimap< std::string, std::string > subscription_list;
				subscription_list subscriptions_;
			public:
				explicit algorithms_engine();
				~algorithms_engine();
				//
			};
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHMS_ENGINE_H_
