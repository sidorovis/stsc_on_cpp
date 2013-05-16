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
			algorithm_manager algorithm_manager_;

			long eod_from_;
			long eod_to_;
			common::shared_name_storage stock_names_;

		public:
			explicit simulator();
			~simulator();
			//
			void clear();
			void set_processing_period( const long eod_from, const long eod_to );

			template< typename iterator >
			void set_stock_names( iterator from, iterator to );
		};

		template< typename iterator >
		void simulator::set_stock_names( iterator from, iterator to )
		{
			for( iterator i = from ; i != to ; ++i )
				stock_names << *i;
		}
	}
}

#endif // _STSC_ENGINE_SIMULATOR_H_
