#ifndef _STSC_COMMON_BAR_TYPES_H_
#define _STSC_COMMON_BAR_TYPES_H_

#include <ostream>

namespace stsc
{
	namespace common
	{
		struct bar_type
		{
			typedef float float_type;

			float_type open_;
			float_type close_;
			float_type high_;
			float_type low_;

			float_type volume_;
		};
		std::ostream& operator<<( std::ostream& out, const bar_type& bar );
	}
}

#endif // _STSC_COMMON_BAR_TYPES_H_

