
#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

#include <csv/yahoo_finance_reader.h>
#include <csv/yahoo_finance_reader_to_binary_processor.h>

int main( const int argc, char* const argv[] )
{
	using namespace boost::filesystem;

	const path filename_path( argv[0] );
	if ( argc != 3 )
	{
		std::cerr << "usage: " << filename_path.filename() << " yahoo_datafeed_folder binary_output_folder" << std::endl;
		return 0;
	}
	const path from_path( argv[1] );
	const path to_path( argv[2] );

	if ( !exists( from_path ) || !is_directory( from_path ) )
	{
		std::cerr << "bad yahoo datafeed folder: " << from_path << std::endl;
		return 0;
	}
	if ( !exists( to_path ) || !is_directory( to_path ) )
	{
		std::cerr << "bad output folder: " << to_path << std::endl;
		return 0;
	}

	try
	{
		stsc::datafeed::csv::yahoo_finance_to_binary_data processor_;
		stsc::datafeed::csv::yahoo_finance_reader yfr_( processor_, from_path.string(), false );

		yfr_.process( 4ul );

		processor_.save_to( to_path );
	}
	catch( const std::exception& ex )
	{
		std::cerr << ex.what() << std::endl;
	}
}

