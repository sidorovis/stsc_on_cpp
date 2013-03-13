#ifndef _STSC_DATAFEED_DATAFEED_PROCESSOR_H_
#define _STSC_DATAFEED_DATAFEED_PROCESSOR_H_

#include <string>
#include <list>
#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

#include <bar_types.h>

namespace stsc
{
	namespace datafeed
	{
		class datafeed_processor : virtual protected boost::noncopyable
		{
		public:
			explicit datafeed_processor();
			virtual ~datafeed_processor();
			virtual void process_bar( const boost::shared_ptr< std::string >& stock_name, boost::shared_ptr< common::price_bar >& new_bar ) = 0;
			virtual void error_process( const std::string& reason, const std::string& file_path ) = 0;
		};
	}
}


#endif // _STSC_DATAFEED_DATAFEED_PROCESSOR_H_

