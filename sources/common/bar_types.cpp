#include <bar_types.h>


namespace stsc
{
	namespace common
	{
		std::ostream& operator<<( std::ostream& out, const bar_type& bar )
		{
			out << "bar( " << bar.time_ << " )";
			return out;
		}
		std::ostream& operator<<( std::ostream& out, const price_bar& bar )
		{
			out << "bar( " << bar.time_ << "||" << bar.open_ << "|" << bar.high_ << "|" << bar.low_ << "|" << bar.close_ << " " << bar.volume_ << " )";
			return out;
		}

	}
}
