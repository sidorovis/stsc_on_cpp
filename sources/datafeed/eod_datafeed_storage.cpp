#include <eod_datafeed_storage.h>

#include <fstream>

#include <boost/thread.hpp>

#include <binary/reader.h>

namespace stsc
{
	namespace datafeed
	{
		eod_datafeed_storage_manager::eod_datafeed_storage_manager()
		{
		}
		eod_datafeed_storage_manager::~eod_datafeed_storage_manager()
		{
		}
		void eod_datafeed_storage_manager::file_reading_error( const std::string& file_path )
		{
		}
		//
		eod_datafeed_storage::eod_datafeed_storage( eod_datafeed_storage_manager& manager, const std::string& datafeed_file_path, const long from, const long to )
			: manager_( manager )
			, datafeed_file_path_( datafeed_file_path )
			, period_from_( from )
			, period_to_( to )
		{
			if ( period_from_ >= period_to_ )
				throw std::invalid_argument("from should be < than to");

			if ( !( boost::filesystem::exists( datafeed_file_path ) && boost::filesystem::is_directory( datafeed_file_path ) ) )
				throw std::invalid_argument("eod_datafeed_storage constructor should be called with datafeed folder, wrong datafeed folder: '" + datafeed_file_path + "'");

			const common::shared_name_storage& stock_names = manager_.stock_names();
			for( common::shared_name_storage::const_iterator i = stock_names.begin() ; i != stock_names.end() ; ++i )
			{
				preprocess_stock( i.shared() );
			}
		}
		eod_datafeed_storage::~eod_datafeed_storage()
		{
			while ( !stock_names_queue_.empty() )
				stock_names_queue_.pop();
		}
		//
		void eod_datafeed_storage::preprocess_stock( const common::shared_string& stock_name )
		{
			using namespace boost::filesystem;
			const path file_path = datafeed_file_path_ / (*stock_name);
			
			if ( !exists( file_path ) || is_directory( file_path ) )
				throw std::invalid_argument( "no datafeed file '" + *stock_name + "' at " + datafeed_file_path_.string() );

			if ( !stock_names_queue_.push( &stock_name ) )
				throw std::logic_error( "eod_datafeed_storage can't add stock_name to processing queue, it seems that processing had been already finished" );
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
				stock_names_queue::value_type stock_name = stock_names_queue_.ts_pop();
				if ( !stock_name )
					break;
				const boost::filesystem::path file_path = datafeed_file_path_ / *(*stock_name);

				stock_datafeed::datafeed_period p( new binary::period() );
				read_period_( file_path, *p );

				if ( ! p->bars.empty() )
				{
					stock_datafeed_ptr stock_data( new stock_datafeed( *stock_name ) );
					stock_data->set_datafeed( p );
					{
						boost::mutex::scoped_lock lock( protect_datafeed_ );
						datafeed_.insert( std::make_pair( stock_data->current_day(), stock_data ) );
					}
				}
			}
		}
		void eod_datafeed_storage::read_period_( const boost::filesystem::path& from, binary::period& to )
		{
			const std::string file_path = from.string();
			std::ifstream in( file_path.c_str(), std::ios_base::binary );
			if ( !in.is_open() )
				manager_.file_reading_error( file_path );
			else
				read_part( in, to, period_from_, period_to_ );
		}
		//
		std::ostream& operator<<( std::ostream& out, const eod_datafeed_storage& eds )
		{
			out << "eod_datafeed_storage(" << eds.datafeed_file_path_ << " | " << eds.period_from_ << "|" << eds.period_to_ << ")";
			return out;
		}
	}
}

