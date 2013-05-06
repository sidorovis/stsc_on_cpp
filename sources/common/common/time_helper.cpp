#include <common/time_helper.h>

#include <boost/date_time/gregorian/gregorian.hpp>

namespace stsc
{
	namespace common
	{
		const long create_eod_time( const short year, const short month, const short day )
		{
			using namespace boost::gregorian;

			static const date epoch_date( epoch_year_, epoch_month_, epoch_day_ );
			return ( date( year, month, day ) - epoch_date ).days();
		}
		void extract_eod_time( const long time, short& year, short& month, short& day )
		{
			using namespace boost::gregorian;

			static const date epoch_date( epoch_year_, epoch_month_, epoch_day_ );
			const date answer = epoch_date + days( time );
			year = answer.year();
			month = answer.month();
			day = answer.day();
		}
	}
}
