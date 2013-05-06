#include <common/signal_types.h>

namespace stsc
{
	namespace common
	{

		signal::~signal()
		{
		}
		//
		close_signal::~close_signal()
		{
		}
		const signal_type::value close_signal::type() const
		{
			return signal_type::close;
		}
		void close_signal::print( std::ostream& out ) const
		{
			out << "signal(close)";
		}
		//
		open_signal::open_signal( const open_signal::side s )
			: side_( s )
		{
		}
		open_signal::~open_signal()
		{
		}
		const signal_type::value open_signal::type() const
		{
			return signal_type::open;
		}
		void open_signal::print( std::ostream& out ) const
		{
			out << "signal(open|" << side_ << ")";
		}
		//
		std::ostream& operator<<( std::ostream& out, const signal& s )
		{
			s.print( out );
			return out;
		}
	}
}
