#include <bar_types.h>


namespace stsc
{
	namespace common
	{
		std::ostream& operator<<( std::ostream& out, const bar_type& bar )
		{
			out.setf(std::ios::fixed,std::ios::floatfield);
			out.precision( 3 );
			out << "bar( " << bar.open_ << "|" << bar.high_ << "|" << bar.low_ << "|" << bar.close_ << " " << bar.volume_ << " )";
			return out;
		}

	}
}
