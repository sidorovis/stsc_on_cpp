#include <eod_datafeed_storage.h>

#include <fstream>

#include <boost/thread.hpp>

#include <binary/reader.h>

namespace stsc
{
	namespace datafeed
	{
		eod_datafeed_storage::eod_datafeed_storage( datafeed_storage_manager& manager, const std::string& datafeed_file_path )
			: manager_( manager )
			, datafeed_file_path_( datafeed_file_path )
		{
			if ( !( boost::filesystem::exists( datafeed_file_path ) && boost::filesystem::is_directory( datafeed_file_path ) ) )
				throw std::invalid_argument("eod_datafeed_storage constructor should be called with datafeed folder, wrong datafeed folder: '" + datafeed_file_path + "'");
		}
		eod_datafeed_storage::~eod_datafeed_storage()
		{
		}
		//
		void eod_datafeed_storage::add_stock_to_parse( const std::string& stock_name )
		{
			using namespace boost::filesystem;
			const path file_path = datafeed_file_path_ / stock_name;
			if ( !exists( file_path ) || is_directory( file_path ) || names_to_parse_.find( stock_name ) != names_to_parse_.end() )
				throw std::invalid_argument( "no datafeed file '" + stock_name + "' at " + datafeed_file_path_.string() );
			names_to_parse_.insert( stock_name );
			if ( !files_to_parse_.push( new std::string( stock_name ) ) )
				throw std::logic_error( "eod_datafeed_storage can't add file_path to process, it seems that processing had been started before" );
		}
		void eod_datafeed_storage::read_datafeed()
		{
			read_datafeed_from_file_storage_();
		}
		void eod_datafeed_storage::multithread_read_datafeed( const size_t thread_amount )
		{
			boost::thread_group tg;
			for( size_t i = 0 ; i < thread_amount ; ++i )
				tg.create_thread( boost::bind( &eod_datafeed_storage::read_datafeed_from_file_storage_, this ) );
			tg.join_all();
		}
		//
		void eod_datafeed_storage::read_datafeed_from_file_storage_()
		{
			while( true )
			{
				boost::shared_ptr< std::string > stock_name( files_to_parse_.ts_pop() );
				if ( !stock_name )
					break;
				const boost::filesystem::path file_path = datafeed_file_path_ / (*stock_name);
				binary::period* p = market_data_.get_for_edit( *stock_name );
				read_period_( file_path, *p );
			}
		}
		void eod_datafeed_storage::read_period_( const boost::filesystem::path& from, binary::period& to )
		{
			const std::string file_path = from.string();
			std::ifstream in( file_path.c_str(), std::ios::binary );
			if ( !in.is_open() )
				manager_.file_reading_error( file_path );
			else
				in >> to;
		}
		//
		void eod_datafeed_storage::process_period( const long from, const long to )
		{
		}
		//
		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds )
		{
			out << eds.names_to_parse_.size() << std::endl;
			size_t size = 0;
			for( eod_datafeed_storage::stock_names_set::const_iterator i = eds.names_to_parse_.begin() ; i != eds.names_to_parse_.end() ; ++i  )
				size += eds.market_data_.get_for_read( *i )->bars.size();
			out << size << std::endl;
			return out;
		}
	}
}

