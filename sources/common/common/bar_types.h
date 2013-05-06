#ifndef _STSC_COMMON_BAR_TYPES_H_
#define _STSC_COMMON_BAR_TYPES_H_

#include <ostream>

#include <boost/shared_ptr.hpp>

#include <shared_name_storage.h>

namespace stsc
{
	namespace common
	{
		namespace bar_data_type
		{
			enum value
			{
				open,
				high,
				low,
				close,
				volume
			};
		}
		struct bar_type
		{
			long time_;
		};
		struct bar_data
		{
			typedef float float_type;

			float_type open_;
			float_type high_;
			float_type low_;
			float_type close_;

			float_type volume_;
		};
		struct price_bar : public bar_type, public bar_data
		{
		};

		//
		struct on_stock_bar
		{
			const common::price_bar& value;
			const size_t index;
			//
			explicit on_stock_bar( const common::price_bar& b, const size_t i );
		};
		struct on_bar
		{
			const common::bar_type value;
			const size_t index;
			//
			explicit on_bar( const common::bar_type& b, const size_t i );
		};
		struct on_period
		{
			common::bar_type value;
			size_t index;
			//
			explicit on_period( const common::bar_type& b, const size_t i );
			explicit on_period();
		};

		//
		std::ostream& operator<<( std::ostream& out, const bar_type& bar );
		std::ostream& operator<<( std::ostream& out, const price_bar& bar );
	}
}

#endif // _STSC_COMMON_BAR_TYPES_H_

