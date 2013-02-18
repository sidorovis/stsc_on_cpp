#include <bar_types.h>


namespace stsc
{
	namespace common
	{
		namespace
		{
			template< typename float_type >
			void print_bar( std::ostream& out, const bar_type< float_type>& bar )
			{
				out.setf(std::ios::fixed,std::ios::floatfield);
				out.precision( 3 );
				out << "bar( " << bar.open_ << "|" << bar.high_ << "|" << bar.low_ << "|" << bar.close_ << " " << bar.volume_ << " )";
			}
		}

		std::ostream& operator<<( std::ostream& out, const float_bar_type& bar )
		{
			print_bar( out, bar );
			return out;
		}
		std::ostream& operator<<( std::ostream& out, const double_bar_type& bar )
		{
			print_bar( out, bar );
			return out;
		}

	}
}
