#ifndef _STSC_COMMON_TIME_HELPER_H_
#define _STSC_COMMON_TIME_HELPER_H_

namespace stsc
{
	namespace common
	{
		static const long epoch_year_ = 1900;
		static const long epoch_month_ = 1;
		static const long epoch_day_ = 1;

		const long create_eod_time( const short year, const short month, const short day );
		void extract_eod_time( const long time, short& year, short& month, short& day );
	}
}

#endif // _STSC_COMMON_TIME_HELPER_H_