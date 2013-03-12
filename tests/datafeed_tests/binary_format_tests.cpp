#include <test_registrator.h>

#include <fstream>

#include <boost/filesystem.hpp>

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

				void write_read_unit_tests()
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
						std::ifstream out( BINARY_DIR "/binary_writer.test" );
						out >> bp;
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
			}
		}
	}
}
