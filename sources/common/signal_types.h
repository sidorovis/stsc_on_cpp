#ifndef _STSC_COMMON_SIGNAL_TYPES_H_
#define _STSC_COMMON_SIGNAL_TYPES_H_

#include <ostream>

namespace stsc
{
	namespace common
	{
		namespace signal_type
		{
			enum value
			{
				open = 1,
				close = -1
			};
		};

		struct signal
		{
			virtual ~signal();
			virtual const signal_type::value type() const = 0;
			virtual void print( std::ostream& ) const = 0;
		};
		struct close_signal : public signal
		{
			virtual ~close_signal();
			virtual const signal_type::value type() const;
			virtual void print( std::ostream& ) const;
		};
		struct open_signal : public signal
		{
			enum side
			{
				side_long = 1,
				side_short = -1
			};
			side side_;
			explicit open_signal( const open_signal::side s );
			virtual ~open_signal();
			virtual const signal_type::value type() const;
			virtual void print( std::ostream& ) const;
		};

		std::ostream& operator<<( std::ostream&, const signal& );
	}
}

#endif // _STSC_COMMON_SIGNAL_TYPES_H_
