#include <common/bar_types.h>

namespace stsc
{
	namespace common
	{
		on_stock_bar::on_stock_bar( const common::price_bar& b, const size_t i )
			: value( b )
			, index( i )
		{
		}
		on_bar::on_bar( const common::bar_type& b, const size_t i )
			: value( b )
			, index( i )
		{
		}
		on_period::on_period( const common::bar_type& b, const size_t i )
			: value( b )
			, index( i )
		{
		}
		on_period::on_period()
		{
		}
		//
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
