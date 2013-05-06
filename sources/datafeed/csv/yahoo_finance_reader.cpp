#include <csv/yahoo_finance_reader.h>

#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

#include <common/time_helper.h>

namespace stsc
{
	namespace datafeed
	{
		namespace csv
		{
			namespace details
			{
				yahoo_finance_file::yahoo_finance_file( const std::string& fn, const std::string& fp )
					: file_name( fn )
					, file_path( fp )
				{
				}
			}

			//
			yahoo_finance_reader::yahoo_finance_reader( stock_datafeed_processor& dp, const std::string& datafeed_folder, const bool protected_scan )
				: datafeed_processor_( dp )
				, protected_scan_( protected_scan )
			{
				using namespace boost::filesystem;
				path datafeed_path( datafeed_folder );

				if ( !exists( datafeed_path ) || !is_directory( datafeed_path ) )
					throw std::logic_error( "datafeed_folder: " + datafeed_folder + " should exists and be directory" );

				for ( directory_iterator i( datafeed_path ), end ; i != end ; ++i )
				{
					const std::string file_path = i->string();
					const std::string file_name = i->path().filename();

					if ( file_is_datafeed_file_( file_name ) )
						datafeed_files_.push_back( details::yahoo_finance_file_ptr( new details::yahoo_finance_file( file_name, file_path ) ) );
				}
			}
			yahoo_finance_reader::~yahoo_finance_reader()
			{
			}
			//
			void yahoo_finance_reader::process( const size_t thread_size )
			{
				boost::thread_group tg;
				for( size_t i = 0 ; i < thread_size ; ++i )
					tg.create_thread( boost::bind( &yahoo_finance_reader::processing_thread_, this ) );
				tg.join_all();
			}
			//
			bool yahoo_finance_reader::file_is_datafeed_file_( const std::string& file_name )
			{
				const boost::regex r("[a-zA-Z]{1,8}\\.csv");
				return boost::regex_match( file_name, r );
			}
			void yahoo_finance_reader::processing_thread_()
			{
				while( true )
				{
					const details::yahoo_finance_file_ptr file_description = file_path_to_process_();

					if ( !file_description )
						break;
					std::ifstream input_file( file_description->file_path.c_str() );
					if ( !input_file.is_open() )
					{
						datafeed_processor_.error_process( "file cannot be opened", file_description->file_path );
						continue;
					}
					if ( !first_line_is_correct_( input_file ) )
					{
						datafeed_processor_.error_process( "first line of file is incorrect", file_description->file_path );
						continue;
					}
					try
					{
						process_datafeed_( input_file, file_description->file_name );
					}
					catch( const std::exception& e )
					{
						datafeed_processor_.error_process( e.what(), file_description->file_path );
					}
					input_file.close();
				}
			}
			const details::yahoo_finance_file_ptr yahoo_finance_reader::file_path_to_process_()
			{
				boost::mutex::scoped_lock lock( file_vector_mutex_ );
				if ( datafeed_files_.empty() )
					return details::yahoo_finance_file_ptr();
				const details::yahoo_finance_file_ptr result = datafeed_files_.back();
				datafeed_files_.pop_back();
				return result;
			}
			//
			const bool yahoo_finance_reader::first_line_is_correct_( std::ifstream& file )
			{
				std::string line;
				std::getline( file, line );
				const boost::regex r("Date,Open,High,Low,Close,Volume,Adj Close");
				return boost::regex_match( line, r );
			}
			void yahoo_finance_reader::process_datafeed_( std::ifstream& file, const std::string& file_name )
			{
				typedef boost::shared_ptr< std::string > stock_name_ptr;
				const stock_name_ptr stock_name( new std::string( create_stock_name_( file_name ) ) );
				const boost::regex r( "(\\d{4})-(\\d{2})-(\\d{2}),([\\d\\.]+),([\\d\\.]+),([\\d\\.]+),([\\d\\.]+),([\\d]+),([\\d\\.]+)" );
				std::string line;
				size_t index_line = 1;
				short year = 0, month = 0, day = 0;
				while ( !file.eof() )
				{
					std::getline( file, line );
					if ( line.empty() )
						continue;

					if ( protected_scan_ && !boost::regex_match( line, r ) )
						throw std::logic_error( "error while parsing line: " + boost::lexical_cast< std::string >( index_line )  + "(" + file_name + ")" );

					common::price_bar bar;

					const int elements = sscanf( line.c_str(), "%hd-%hd-%hd,%f,%f,%f,%f,%f", 
						&year,
						&month,
						&day,
						&(bar.open_),
						&(bar.high_),
						&(bar.low_),
						&(bar.close_),
						&(bar.volume_)
						 );
					static const int right_element_amount = 8;
					if ( elements != right_element_amount )
						throw std::logic_error( "bad line: '" + line + "' at line: " + boost::lexical_cast< std::string >( index_line ) + "(" + file_name + ")"  ); 
					bar.time_ = common::create_eod_time( year, month, day );
					datafeed_processor_.process_bar( stock_name, bar );
					++index_line;
				}
			}
			const std::string yahoo_finance_reader::create_stock_name_( const std::string& file_name )
			{
				std::string stock_name;
				const boost::regex r( "(\\w+)\\.csv" );
				boost::smatch m;
				if( boost::regex_match( file_name, m, r ) )
				{
					stock_name = m[1];
					boost::to_lower( stock_name );
					if ( stock_name.empty() )
						throw std::logic_error( "no stock_name on file name: " + file_name ); 
				}
				else
					throw std::logic_error("bad file name, no stock_name value at file name: " + file_name);

				return stock_name;
			}
		}
	}
}
