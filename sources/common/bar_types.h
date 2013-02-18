#ifndef _STSC_COMMON_BAR_TYPES_H_
#define _STSC_COMMON_BAR_TYPES_H_

#include <ostream>

namespace stsc
{
	namespace common
	{
		template< typename float_type_typename = float >
		struct bar_type
		{
			typedef float_type_typename float_type;

			float_type open_;
			float_type close_;
			float_type high_;
			float_type low_;

			float_type volume_;
		};
		typedef bar_type< float > float_bar_type;
		typedef bar_type< double > double_bar_type;

		std::ostream& operator<<( std::ostream& out, const float_bar_type& bar );
		std::ostream& operator<<( std::ostream& out, const double_bar_type& bar );
	}
}

#endif // _STSC_COMMON_BAR_TYPES_H_

