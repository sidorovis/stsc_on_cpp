#include <test_registrator.h>

#include <boost/filesystem.hpp>

#include <csv/yahoo_finance_reader_to_binary_processor.h>
#include <csv/yahoo_finance_reader.h>

#include <binary/reader.h>

using namespace stsc::datafeed::csv;

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			namespace csv
			{
				namespace 
				{
					stsc::datafeed::binary::period check_binary_datafeed_exists( const std::string& file_path, const size_t bars_size )
					{
						using namespace boost::filesystem;

						BOOST_CHECK_EQUAL( exists( file_path ), true );
						stsc::datafeed::binary::period p;
						std::ifstream file( file_path.c_str() );
						file >> p;
						file.close();
						BOOST_CHECK_EQUAL( p.header.elements_size, bars_size );
						BOOST_CHECK_EQUAL( p.bars.size(), bars_size );
						BOOST_CHECK_NO_THROW( boost::filesystem::remove( file_path ) );
						return p;
					}
				}
				void yahoo_finance_to_binary_data_unit_tests()
				{
					yahoo_finance_to_binary_data yf2bd;
					
					boost::shared_ptr< std::string > aapl( new std::string( "aapl" ) );
					
					common::price_bar new_bar;
					new_bar.time_ = 15000u;
					new_bar.volume_ = 100.0f;
					new_bar.open_ = 15.5f;
					new_bar.high_ = 15.8f;
					new_bar.low_ = 15.3f;
					new_bar.close_ = 15.4f;

					BOOST_CHECK_NO_THROW( yf2bd.process_bar( aapl, new_bar ) );
					BOOST_CHECK_NO_THROW( yf2bd.save_to( boost::filesystem::path( BINARY_DIR ) ) );

					stsc::datafeed::binary::period p = check_binary_datafeed_exists( BINARY_DIR "/aapl", 1ul );

					BOOST_CHECK_EQUAL( p.header.finished, 1ul );
					BOOST_CHECK_EQUAL( p.header.version, 1ul );

					BOOST_CHECK_EQUAL( p.bars[0].time_, 15000u );
					BOOST_CHECK_EQUAL( p.bars[0].volume_, 100.0f );
					BOOST_CHECK_EQUAL( p.bars[0].open_, 15.5f );
					BOOST_CHECK_EQUAL( p.bars[0].high_, 15.8f );
					BOOST_CHECK_EQUAL( p.bars[0].low_, 15.3f );
					BOOST_CHECK_EQUAL( p.bars[0].close_, 15.4f );
				}
				void yahoo_finance_to_binary_data_integration_tests()
				{
					{
						yahoo_finance_to_binary_data yf2bd;
						yahoo_finance_reader yfr( yf2bd, SOURCE_DIR "/tests/data/yahoo_finance_to_binary_data", false  );
						BOOST_CHECK_NO_THROW( yfr.process( 4ul ) );
						BOOST_CHECK_NO_THROW( yf2bd.save_to( boost::filesystem::path( BINARY_DIR ) ) );
					}
					check_binary_datafeed_exists( BINARY_DIR "/aapl", 7188u );
					check_binary_datafeed_exists( BINARY_DIR "/epam", 272u );
					check_binary_datafeed_exists( BINARY_DIR "/goog", 2154u );
					check_binary_datafeed_exists( BINARY_DIR "/spy", 5065u );
				}
			}
		}
	}
}
