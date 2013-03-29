#include <binary/reader.h>

#include <algorithm>
#include <functional> 

namespace stsc
{
	namespace datafeed
	{
		namespace binary
		{
			namespace
			{
				static const long no_intervale_in_file = -1;
				/// returns -1 if bar with time look_for was found;
				void read_header( std::istream& in, binary::period_header& ph )
				{
					typedef char* intype;
					static const size_t header_size = sizeof( binary::period_header );
					in.read( reinterpret_cast< intype >( &ph ), header_size );
				}
				void read_bars( std::istream& in, binary::period& p, const size_t elements_size )
				{
					typedef char* intype;
					p.bars.resize( elements_size );
					static const size_t bar_size = sizeof( common::price_bar );
					in.read( reinterpret_cast< intype >( &( p.bars[0] ) ), bar_size * elements_size );
				}
				struct bar_time_comparator : public std::binary_function< const common::price_bar&, const common::price_bar&, const bool >
				{
					result_type operator()( first_argument_type left, second_argument_type right )
					{
						return left.time_ < right.time_;
					}
				};
			}

			std::istream& operator>>( std::istream& in, binary::period& bp )
			{
				read_header( in, bp.header );
				read_bars( in, bp, bp.header.elements_size );
				return in;
			}

			std::istream& read_part( std::istream& in, binary::period& bp, const long from, const long to )
			{
				typedef char* intype;
				binary::period full_period;
				common::price_bar price_bar_to_search;
				in >> full_period;

				price_bar_to_search.time_ = from;
				binary::period::bars_type::const_iterator start = std::lower_bound( full_period.bars.begin(), full_period.bars.end(), price_bar_to_search, bar_time_comparator() );
				price_bar_to_search.time_ = to;
				binary::period::bars_type::const_iterator end = std::upper_bound( full_period.bars.begin(), full_period.bars.end(), price_bar_to_search, bar_time_comparator() );

				const size_t elements_size = end - start;
				bp.header.elements_size = static_cast< boost::uint32_t >( elements_size );
				bp.bars.resize( elements_size );
				std::copy( start, end, bp.bars.begin() );
				bp.header.finished = full_period.header.finished;
				bp.header.version = full_period.header.version;

				return in;
			}
		}
	}
}
