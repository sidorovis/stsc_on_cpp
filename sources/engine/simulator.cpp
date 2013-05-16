#include <simulator.h>

namespace stsc
{
	namespace engine
	{
		simulator::simulator()
			: algorithm_manager_( stock_names_ )
		{
			clear();
		}
		simulator::~simulator()
		{
		}
		//
		void simulator::clear()
		{
			eod_from_ = 0;
			eod_to_ = 0;
			stock_names_.clear();
		}
		void simulator::set_processing_period( const long eod_from, const long eod_to )
		{
			eod_from_ = eod_from;
			eod_to_ = eod_to;
		}
	}
}
