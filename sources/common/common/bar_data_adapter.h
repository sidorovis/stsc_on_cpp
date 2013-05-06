#ifndef _STSC_COMMON_BAR_DATA_ADAPTER_H_
#define _STSC_COMMON_BAR_DATA_ADAPTER_H_

#include <common/bar_types.h>

namespace stsc
{
	namespace common
	{
		template< bar_data_type::value T = bar_data_type::close >
		struct bar_data_adapter
		{
			static const bar_data::float_type get( const bar_data& b )
			{
				return b.close_;
			}
		};
		template<>
		struct bar_data_adapter< bar_data_type::close > 
		{	
			static const bar_data::float_type get( const bar_data& b )
			{
				return b.close_;
			}
		};
		template<>
		struct bar_data_adapter< bar_data_type::open > 
		{	
			static const bar_data::float_type get( const bar_data& b )
			{
				return b.open_;
			}
		};
		template<>
		struct bar_data_adapter< bar_data_type::high > 
		{	
			static const bar_data::float_type get( const bar_data& b )
			{
				return b.high_;
			}
		};
		template<>
		struct bar_data_adapter< bar_data_type::low > 
		{	
			static const bar_data::float_type get( const bar_data& b )
			{
				return b.low_;
			}
		};
		template<>
		struct bar_data_adapter< bar_data_type::volume > 
		{	
			static const bar_data::float_type get( const bar_data& b )
			{
				return b.volume_;
			}
		};
	}
}

#endif // _STSC_COMMON_BAR_DATA_ADAPTER_H_

