#ifndef _STSC_ENGINE_SIMULATOR_H_
#define _STSC_ENGINE_SIMULATOR_H_

#include <boost/noncopyable.hpp>

#include <shared_name_storage.h>

#include <common/types.h>

#include <algorithm_manager.h>


namespace stsc
{
	namespace engine
	{
		class simulator : public boost::noncopyable
		{
			common::shared_name_storage stock_names_;

			algorithm_manager algorithm_manager_;

		public:
			explicit simulator();
			~simulator();
			//
			void read_configuration_file();
			void read_algorithms_file();
		};
	}
}

#endif // _STSC_ENGINE_SIMULATOR_H_
