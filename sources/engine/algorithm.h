#ifndef _STSC_ENGINE_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHM_H_

#include <string>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			struct algorithm_storage;
		}
		class algorithm
		{
			friend struct details::algorithm_storage;

			const std::string name_;
		public:
			explicit algorithm( const std::string& name );
			virtual ~algorithm();
		};

	}
}

#endif // _STSC_ENGINE_ALGORITHM_ALGORITHM_PROTOTYPE_H_
