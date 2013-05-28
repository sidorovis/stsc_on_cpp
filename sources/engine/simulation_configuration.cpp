#include <simulation_configuration.h>

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			parameter::parameter( const std::string& name, const std::string& value )
				: name_( name )
				, value_( value )
			{
			}
			parameter::~parameter()
			{
			}
			bool operator<( const parameter_ptr& first, const parameter_ptr& second )
			{
				return first->name_ < second->name_;
			}
			//
			execution::execution( const std::string& name, const std::string& algorithm_name )
				: name_( name )
				, algorithm_name_( algorithm_name )
			{
			}
			execution::~execution()
			{
			}
			execution& execution::add_parameter( const parameter_ptr& p )
			{
				parameters_.push_back( p );
				return *this;
			}
			void execution::sort()
			{
				std::sort( parameters_.begin(), parameters_.end() );
			}
			const parameter_list& execution::parameters() const
			{
				return parameters_;
			}
			bool operator<( const execution_ptr& first, const execution_ptr& second )
			{
				return first->name_ < second->name_;
			}
			bool operator==( const execution_ptr& first, const std::string& execution_name )
			{
				return first->name_ == execution_name;
			}
			//
			execution_ptr make_execution( const std::string& name, const std::string& algorithm_name )
			{
				return execution_ptr( new execution( name, algorithm_name ) );
			}
			//
			stock_set::stock_set( const stock_set::stock_names& names )
				: stock_names_( names )
			{
			}
			void stock_set::add_execution( const std::string& execution_name, const execution_ptr& e )
			{
				std::stringstream stock_set_str;
				for( stock_names::const_iterator i = stock_names_.begin() ; i != stock_names_.end() ; ++i )
					stock_set_str << *(*i) << " ";
				if ( !executions_.insert( std::make_pair( execution_name, e ) ).second )
					throw std::logic_error( "it seems that execution '" + execution_name + "' had been added before for stock set: " + stock_set_str.str() );
			}
			bool stock_set::find_execution_name( const std::string& execution_name ) const
			{
				return executions_.find( execution_name ) != executions_.end();
			}
		};
		simulation_configuration::simulation_configuration( const common::shared_name_storage& stock_names )
			: stock_names_( stock_names )
		{
		}
		simulation_configuration::~simulation_configuration()
		{
			clear();
		}
		//
		void simulation_configuration::clear()
		{
			configuration_.clear();
			current_stock_set_.reset();
		}
		//
		const std::string simulation_configuration::line_index_str_( const size_t line_index )
		{
			return boost::lexical_cast< std::string >( line_index );
		}
		//
		void simulation_configuration::read( std::istream& in )
		{
			size_t line_index = 0;
			while ( !in.eof() )
			{
				std::string line;
				std::getline( in, line );
				++line_index;
				
				trim_line_( line );

				if ( line.empty() )
					continue;

				check_and_append_next_line_( line, in, line_index );

				if ( line.empty() )
					continue;

				if ( comment_( line ) )
					continue;

				process_line_( line, line_index );
			}
			if ( current_stock_set_.get() )
				configuration_.push_back( current_stock_set_ );
		}
		//
		std::string& simulation_configuration::trim_line_( std::string& line )
		{
			boost::algorithm::trim( line );
			return line;
		}
		void simulation_configuration::check_and_append_next_line_( std::string& line, std::istream& in, size_t& line_index )
		{
			if ( in.eof() )
				throw std::logic_error("last configuration line can't have '\\' symbol (line:" + line_index_str_( line_index ) + ")");
			while ( !in.eof() && line[ line.size() - 1 ] == '\\' )
			{
				std::string line_extension;
				std::getline( in, line_extension );
				++line_index;
				
				trim_line_( line_extension );

				line.erase( line.size() - 1, 1 );
				line += line_extension;

				if ( !line.empty() && line[ line.size() - 1 ] == '\\' && in.eof() )
					throw std::logic_error("last configuration line can't have '\\' symbol (line:" + line_index_str_( line_index ) + ")");
			}
		}
		bool simulation_configuration::comment_( const std::string& line )
		{
			return line[0] == '#';
		}
		std::string& simulation_configuration::delete_brackets_from_parameter_value_( std::string& value, char bracket_type, const std::string& execution_name, const std::string& line )
		{
			if ( !value.empty() && value[0] == bracket_type )
			{
				const size_t line_size = value.size();
				if ( line_size == 1ul || value[ line_size - 1 ] != bracket_type )
					throw std::invalid_argument( "bad parameter at execution line '" + execution_name + "' (" + line + "), " + bracket_type + " brackets incorrect" );
				else
					value = value.substr( 1ul, line_size - 2 );
			}
			return value;
		}

		void simulation_configuration::process_line_( const std::string& line, const size_t line_index )
		{
			if ( line[0] == '[' )
				process_instrument_list_( line, line_index );
			else
			if ( line[0] == '|' )
				process_assignment_( line, line_index );
			else
				throw std::logic_error( "bad line at " + line_index_str_( line_index ) + " it should start from '[' or '|' " );
		}
		void simulation_configuration::process_instrument_list_( const std::string& line, const size_t line_index )
		{
			if ( line.empty() || line[0] != '[' || line[ line.size() - 1 ] != ']' )
				throw std::invalid_argument("line '" + line + "' should be instrument line (for example: [aapl,goog])");

			typedef std::list< std::string > string_list;
			string_list names;
			boost::algorithm::split( names, line.substr( 1, line.size() - 2 ), boost::algorithm::is_any_of(",") );
			details::stock_set::stock_names init;
			
			for( string_list::const_iterator i = names.begin() ; i != names.end() ; ++i )
			{
				common::shared_string ss = stock_names_.get_shared( boost::algorithm::trim_copy( *i ) );
				if ( !ss.get() || (*ss).empty() )
					throw std::logic_error( "line: '" + line + "' have stock name (" + *i + ") that was not inserted into initial stock set" );
				init.insert( ss );
			}
			if ( current_stock_set_.get() )
				configuration_.push_back( current_stock_set_ );

			current_stock_set_.reset( new details::stock_set( init ) );
		}
		void simulation_configuration::process_assignment_( const std::string& line, const size_t line_index )
		{
			if ( line.empty() || line[0] != '|' )
				throw std::invalid_argument( "line '" + line + "' should be algorithm line (start from '|')" );
			if ( !current_stock_set_.get() )
				throw std::logic_error( "line '" + line + "' not included into stock set configuration, please add instrument line before (for example [aapl])" );

			std::string execution_name, algorithm_name, parameters_str;

			divide_assignment_line_( line, line_index, execution_name, algorithm_name, parameters_str );

			if ( current_stock_set_->find_execution_name( execution_name ) )
				throw std::logic_error( "adding already existing execution name at line: " + line_index_str_( line_index ) + " with execution_name: " + execution_name );

			details::execution_ptr execution = generate_execution_ptr_( execution_name, algorithm_name, parameters_str );
			current_stock_set_->add_execution( execution_name, execution );
		}
		void simulation_configuration::divide_assignment_line_( const std::string& line, const size_t line_index, std::string& execution_name, std::string& algorithm_name, std::string& parameters_str )
		{
			const boost::regex r( "\\| *(\\w+) *= *(\\w+)\\((.*)\\)" );
			boost::smatch s;
			if ( boost::regex_match( line, s, r ) )
			{
				execution_name = s[1];
				algorithm_name = s[2];
				parameters_str = s[3];
			}
			else
				throw std::invalid_argument("bad algorithm execution line '" + line + "' on " + line_index_str_( line_index ));
		}
		details::execution_ptr simulation_configuration::generate_execution_ptr_( const std::string& execution_name, const std::string& algorithm_name, const std::string& parameters_str )
		{
			details::execution_ptr result = details::make_execution( execution_name, algorithm_name );

			if ( parameters_str.empty() )
				return result; 

			typedef std::vector< std::string > strings;
			strings parameters_vector;

			boost::algorithm::split( parameters_vector, parameters_str, boost::algorithm::is_any_of( "," ) );
			for( strings::iterator i = parameters_vector.begin() ; i != parameters_vector.end() ; ++i )
			{
				const std::string& line = trim_line_( *i );
				const boost::regex check_parameter( "(\\w+) *= *(.+)" );
				const boost::regex check_in_algorithm( "(\\w+)" );
				boost::smatch match;
				if ( boost::regex_match( line, match, check_parameter ) )
				{
					const std::string name = match[1];
					std::string value = match[2];

					if ( value.empty() )
						throw std::invalid_argument( "bad parameter at execution line '" + execution_name + "' (" + line + "), it cannot be blank" );

					delete_brackets_from_parameter_value_( value, '"', execution_name, line );
					delete_brackets_from_parameter_value_( value, '\'', execution_name, line );

					result->add_parameter( name, value );
				}
				else
				if ( boost::regex_match( line, match, check_in_algorithm ) )
				{
					const std::string algo_name = match[1];
					if ( !current_stock_set_->find_execution_name( algo_name ) )
						throw std::invalid_argument( "bad parameter at execution line '" + execution_name + "' (" + line + "), " + algo_name + " execution not registered at stock set" );
				}
				else
					throw std::invalid_argument( "bad parameter at execution line '" + execution_name + "' (" + line + "), unknown parameter" );
			}

			return result;
		}
	}
}
