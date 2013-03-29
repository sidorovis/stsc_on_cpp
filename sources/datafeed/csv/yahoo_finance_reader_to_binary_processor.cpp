#include <csv/yahoo_finance_reader_to_binary_processor.h>

#include <iostream>

#include <algorithm>

#include <binary/writer.h>

namespace stsc
{
	namespace datafeed
	{
		namespace csv
		{

			yahoo_finance_to_binary_data::yahoo_finance_to_binary_data()
			{
			}
			yahoo_finance_to_binary_data::~yahoo_finance_to_binary_data()
			{
			}
			//
			void yahoo_finance_to_binary_data::process_bar( const stock_name_ptr& stock_name, const common::price_bar& new_bar )
			{
				datafeed::binary::period& binary_period = period( stock_name );
				binary_period.bars.push_back( new_bar );
			}
			void yahoo_finance_to_binary_data::error_process( const std::string& reason, const std::string& file_path )
			{
				std::cerr << "error: " << reason << " while parsing " << file_path << std::endl;
			}
			//
			datafeed::binary::period& yahoo_finance_to_binary_data::period( const stock_name_ptr& stock_name )
			{
				boost::mutex::scoped_lock lock( protect_datafeed_ );
				return datafeed_[ stock_name ];
			}
			void yahoo_finance_to_binary_data::save_to( const boost::filesystem::path& output_folder ) const
			{
				boost::mutex::scoped_lock lock( protect_datafeed_ );
				for( datafeed_map::iterator i = datafeed_.begin() ; i != datafeed_.end() ; ++i )
				{
					const std::string file_path = (output_folder / (*i->first)).string();
					std::ofstream file( file_path.c_str(), std::ios_base::binary );

					datafeed::binary::period& p = i->second;

					std::reverse( p.bars.begin(), p.bars.end() );

					p.header.finished = 1ul;
					p.header.version = 1ul;
					p.header.elements_size = static_cast< boost::uint32_t >( p.bars.size() );

					file << p;

					file.close();
				}
			}
		}
	}
}


