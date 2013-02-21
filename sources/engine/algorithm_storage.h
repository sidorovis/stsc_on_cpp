#ifndef _STSC_ALGORITHM_STORAGE_ALGORITHM_STORAGE_H_
#define _STSC_ALGORITHM_STORAGE_ALGORITHM_STORAGE_H_

#include <boost/noncopyable.hpp>

#include <algorithm_prototype.h>

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

				template< typename input_bar_type, typename output_signal_type >
				void insert( algorithm_prototype< input_bar_type, output_signal_type >* const algo )
				{
					data_.insert( std::make_pair( algo->name_, algo ) );
				}
				template< typename input_bar_type, typename output_signal_type >
				void erase( algorithm_prototype< input_bar_type, output_signal_type >* const algo )
				{
					data_.erase( algo->name_ );
				}
			};
			std::ostream& operator<<( std::ostream& out, const algorithm_storage& as );
		}
	}
}

#endif // _STSC_ALGORITHM_STORAGE_ALGORITHM_STORAGE_H_