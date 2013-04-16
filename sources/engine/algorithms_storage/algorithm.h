#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_H_

#include <string>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			namespace details
			{
				class algorithm
				{
					friend class algorithms;

					const std::string name_;
				public:
					explicit algorithm( const std::string& name );
					virtual ~algorithm();
				};
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_H_
