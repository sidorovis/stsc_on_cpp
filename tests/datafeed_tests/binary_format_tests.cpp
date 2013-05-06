#include <test_registrator.h>

#include <fstream>

#include <boost/filesystem.hpp>

#include <common/time_helper.h>

#include <binary/writer.h>
#include <binary/reader.h>

using namespace stsc::datafeed::binary;

namespace stsc
{
	namespace tests_
	{
		namespace datafeed
		{
			namespace binary
			{
				namespace
				{
					period period_write_read_part_unit_tests_helper( const std::string& file_name, const long from, const long to )
					{
						std::ifstream in( file_name.c_str(), std::ios_base::binary );
						period bp;
						read_part( in, bp, from, to );
						return bp;
					}
				}

				void period_header_sizeof_tests()
				{
					BOOST_CHECK_EQUAL( sizeof( common::bar_type ), 4ul );
					BOOST_CHECK_EQUAL( sizeof( common::bar_data ), 20ul );
					BOOST_CHECK_EQUAL( sizeof( common::price_bar ), 24ul );
					BOOST_CHECK_EQUAL( sizeof( period_header ), 12ul );
				}
				void period_constructor_tests()
				{
					BOOST_CHECK_NO_THROW( period() );
				}

				void period_write_read_unit_tests()
				{
					{
						period bp;
						bp.header.finished = 1u;
						bp.header.version = 1u;
						bp.header.elements_size = 2u;
						bp.bars.resize( 2u );
						bp.bars[0].time_ = 100;
						bp.bars[0].close_ = 12.43f;
						bp.bars[0].low_ = 22.43f;
						bp.bars[0].high_ = 32.43f;
						bp.bars[0].open_ = 52.43f;
						bp.bars[0].volume_ = 100000.0f;
						bp.bars[1].time_ = 101;
						bp.bars[1].close_ = 92.43f;
						bp.bars[1].low_ = 82.43f;
						bp.bars[1].high_ = 72.43f;
						bp.bars[1].open_ = 62.43f;
						bp.bars[1].volume_ = 1000.0f;
						std::ofstream out( BINARY_DIR "/binary_writer.test" );
						out << bp;
					}
					BOOST_CHECK_EQUAL( boost::filesystem::exists( BINARY_DIR "/binary_writer.test" ), true );
					BOOST_CHECK_EQUAL( boost::filesystem::file_size( BINARY_DIR "/binary_writer.test" ), 60ul );
					{
						period bp;
						std::ifstream in( BINARY_DIR "/binary_writer.test" );
						in >> bp;
						BOOST_CHECK_EQUAL( bp.header.finished, 1u );
						BOOST_CHECK_EQUAL( bp.header.version, 1u );
						BOOST_CHECK_EQUAL( bp.header.elements_size, 2u );

						BOOST_CHECK_EQUAL( bp.bars.size(), 2ul );

						BOOST_CHECK_EQUAL( bp.bars[0].time_, 100l );
						BOOST_CHECK_EQUAL( bp.bars[1].time_, 101l );

						BOOST_CHECK_EQUAL( bp.bars[0].close_, 12.43f );
						BOOST_CHECK_EQUAL( bp.bars[1].close_, 92.43f );

						BOOST_CHECK_EQUAL( bp.bars[0].high_, 32.43f );
						BOOST_CHECK_EQUAL( bp.bars[1].high_, 72.43f );

						BOOST_CHECK_EQUAL( bp.bars[0].volume_, 100000.0f );
						BOOST_CHECK_EQUAL( bp.bars[1].volume_, 1000.0f );
					}
					BOOST_CHECK_NO_THROW( boost::filesystem::remove( BINARY_DIR "/binary_writer.test" ) );
				}

				void period_write_read_part_unit_tests()
				{
					{
						period bp;
						bp.header.finished = 1u;
						bp.header.version = 1u;
						bp.header.elements_size = 15u;
						bp.bars.resize( 15u );
						for ( long i = 0 ; i < 10 ; ++i )
							bp.bars[ i ].time_ = i;
						for ( long i = 10 ; i < 15 ; ++i )
							bp.bars[ i ].time_ = i + 3;
						std::ofstream out( BINARY_DIR "/binary_writer_read_part.test" );
						out << bp;
					}
					BOOST_CHECK_EQUAL( boost::filesystem::exists( BINARY_DIR "/binary_writer_read_part.test" ), true );
					BOOST_CHECK_EQUAL( boost::filesystem::file_size( BINARY_DIR "/binary_writer_read_part.test" ), 372ul );
					{
						period bp;
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( BINARY_DIR "/binary_writer_read_part.test", 0, 15 ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 13ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( BINARY_DIR "/binary_writer_read_part.test", 9, 15 ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 4ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( BINARY_DIR "/binary_writer_read_part.test", 11, 20 ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 5ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( BINARY_DIR "/binary_writer_read_part.test", 5, 20 ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 10ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( BINARY_DIR "/binary_writer_read_part.test", 8, 11 ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 2ul );
					}
					BOOST_CHECK_NO_THROW( boost::filesystem::remove( BINARY_DIR "/binary_writer_read_part.test" ) );
					{
						period bp;

						long from = common::create_eod_time( 2010, 01, 01 );
						long to = common::create_eod_time( 2010, 12, 31 );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/a", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 252ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/amh", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 231ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/xynh", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 242ul );

						from = common::create_eod_time( 2010, 01, 01 );
						to = common::create_eod_time( 2013, 12, 31 );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/a", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 801ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/amh", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 606ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/xynh", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 736ul );

						from = common::create_eod_time( 1990, 01, 01 );
						to = common::create_eod_time( 1990, 12, 31 );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/a", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 0ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/amh", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 0ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/xynh", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 0ul );
						BOOST_CHECK_NO_THROW( bp = period_write_read_part_unit_tests_helper( SOURCE_DIR "/tests/data/binary_data_example/tpam", from, to ) );
						BOOST_CHECK_EQUAL( bp.bars.size(), 253ul );
					}
				}
			}
		}
	}
}
