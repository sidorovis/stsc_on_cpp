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
			template< typename input_bar_type, typename output_signal_type >
			class algorithm_prototype;

			struct algorithm_storage
			{
				typedef algorithm* const const_pointer;
				typedef std::map< std::string, const_pointer > algorithms;
				algorithms data_;

				template< typename input_bar_type, typename output_signal_type >
				void insert( algorithm_prototype< input_bar_type, output_signal_type >* const algo );

				template< typename input_bar_type, typename output_signal_type >
				void erase( algorithm_prototype< input_bar_type, output_signal_type >* const algo );
			};
			std::ostream& operator<<( std::ostream& out, const algorithm_storage& as );
		}
	}
}

#include <algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			template< typename input_bar_type, typename output_signal_type >
			void algorithm_storage::insert( algorithm_prototype< input_bar_type, output_signal_type >* const algo )
			{
				data_.insert( std::make_pair( algo->name_, algo ) );
			}
			template< typename input_bar_type, typename output_signal_type >
			void algorithm_storage::erase( algorithm_prototype< input_bar_type, output_signal_type >* const algo )
			{
				data_.erase( algo->name_ );
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHM_STORAGE_H_