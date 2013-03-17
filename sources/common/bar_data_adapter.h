#ifndef _STSC_COMMON_BAR_DATA_ADAPTER_H_
#define _STSC_COMMON_BAR_DATA_ADAPTER_H_

#include <bar_types.h>

namespace stsc
{
	namespace engine
	{
		template< stsc::common::bar_data_types::value T = stsc::common::bar_data_types::close >
		struct bar_data_adapter
		{
			static const stsc::common::bar_data::float_type get( const stsc::common::bar_data& b )
			{
				return b.close_;
			}
		};
		template<>
		struct bar_data_adapter< stsc::common::bar_data_types::close > 
		{	
			static const stsc::common::bar_data::float_type get( const stsc::common::bar_data& b )
			{
				return b.close_;
			}
		};
		template<>
		struct bar_data_adapter< stsc::common::bar_data_types::open > 
		{	
			static const stsc::common::bar_data::float_type get( const stsc::common::bar_data& b )
			{
				return b.open_;
			}
		};
		template<>
		struct bar_data_adapter< stsc::common::bar_data_types::high > 
		{	
			static const stsc::common::bar_data::float_type get( const stsc::common::bar_data& b )
			{
				return b.high_;
			}
		};
		template<>
		struct bar_data_adapter< stsc::common::bar_data_types::low > 
		{	
			static const stsc::common::bar_data::float_type get( const stsc::common::bar_data& b )
			{
				return b.low_;
			}
		};
		template<>
		struct bar_data_adapter< stsc::common::bar_data_types::volume > 
		{	
			static const stsc::common::bar_data::float_type get( const stsc::common::bar_data& b )
			{
				return b.volume_;
			}
		};
	}
}

#endif // _STSC_COMMON_BAR_DATA_ADAPTER_H_

