#ifndef _STSC_EOD_DATAFEED_SPITTER_H_
#define _STSC_EOD_DATAFEED_SPITTER_H_

#include <string>
#include <list>
#include <map>
#include <ostream>

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

#include <ts_queue.h>

#include <common/types.h>

#include <binary/format.h>

#include <stock_datafeed.h>

namespace stsc
{
	namespace datafeed
	{
		class eod_datafeed_storage;

		class eod_datafeed_spitter_manager : virtual protected boost::noncopyable
		{
		public:
			eod_datafeed_spitter_manager();
			virtual ~eod_datafeed_spitter_manager();
			//
			virtual void on_stock( const common::shared_string& name, const common::on_stock_bar& bar );
			virtual void on_bar( const common::on_bar& bar );
			virtual void on_period( const common::on_period& bar );
		};

		class eod_datafeed_spitter : protected boost::noncopyable
		{
			eod_datafeed_spitter_manager& manager_;
			
			boost::mutex protect_datafeed_;
			typedef std::multimap< long, stock_datafeed_ptr > sorted_datafeed;
			sorted_datafeed datafeed_;

			typedef std::list< stock_datafeed_ptr > stock_data_list;
			boost::mutex protect_elements_to_delete_insert_;
			stock_data_list elements_to_delete_insert_;
			common::on_period on_period_bar_;

			boost::condition tasks_solved_;
			size_t tasks_to_process_;

			system_utilities::common::ts_queue< sorted_datafeed::const_iterator > processing_bar_tasks_;

		public:
			explicit eod_datafeed_spitter( eod_datafeed_spitter_manager& m, eod_datafeed_storage& storage );
			~eod_datafeed_spitter();
			//
			void spit_datafeed();
			void multithread_spit_datafeed( const size_t thread_amount = 4ul );
		private:
			void add_next_day_();
			void wait_calculating_threads_();
			void process_task_list_();
		};
	}
}

#endif // _STSC_EOD_DATAFEED_SPITTER_H_
