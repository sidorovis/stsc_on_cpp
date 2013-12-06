#ifndef _STSC_ENGINE_SIMULATION_CONFIGURATION_H_
#define _STSC_ENGINE_SIMULATION_CONFIGURATION_H_

#include <string>
#include <vector>
#include <map>
#include <set>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <common/types.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			void simulation_configuration_process_line_tests();
			void simulation_configuration_process_instrument_list_tests();
			void simulation_configuration_process_assignment_tests();
			void simulation_configuration_divide_assignment_line_tests();
			void simulation_configuration_generate_execution_ptr_tests();
		}
	}
	namespace engine
	{
		// configuration file example
		// [aapl, goog, ibm, epam]
		// | a1 = exe( p1 = 'asd', p2 = 42, \
		//      p3 = 45.34, p4 = 'hello' )
		// | a2 = exe2( a1, p2 = 'rfr' )
		// | a3 = exe3( a2, a1 )

		namespace details
		{
			class parameter
			{
			public:
				const std::string name_;
				const std::string value_;

				explicit parameter( const std::string& name, const std::string& value );
				template< typename type >
				explicit parameter( const std::string& name, const type& value )
					: name_( name )
					, value_( boost::lexical_cast< std::string >( value ) )
				{
				}
				~parameter();

				template< typename type >
				const type value() const
				{
					return boost::lexical_cast< type >( value_ );
				}
			};
			typedef boost::shared_ptr< parameter > parameter_ptr;

			bool operator<( const parameter_ptr& first, const parameter_ptr& second );
			bool operator<( const parameter_ptr& first, const std::string& second );
			bool operator==( const parameter_ptr& first, const std::string& second );

			template< typename type >
			parameter_ptr make_parameter( const std::string& name, const type& value )
			{
				return parameter_ptr( new parameter( name, value ) );
			}
			//
			typedef std::map< std::string, parameter_ptr > parameter_map;
			//
			class execution
			{
			public:
				static const char STOCK = 'S';
				static const char BAR = 'B';
				static const char PERIOD = 'P';

				const std::string name_;
				const char type_;
				const std::string algorithm_name_;

				typedef std::vector< std::string > used_executions;
			private:
				parameter_map parameters_;
				used_executions used_execution_names_;
			public:
				explicit execution( const std::string& name, const char type, const std::string& algorithm_name );
				~execution();
				//
				template< typename type >
				execution& add_parameter( const std::string& p_name, const type& p_value );
				//
				void add_dependencie_algorithm( const std::string& dep_name );
				const used_executions& used() const;
				//
				template< typename value_type >
				const value_type parameter( const std::string& parameter_name ) const;
				//
				const parameter_map& parameters() const;
			};

			template< typename type >
			execution& execution::add_parameter( const std::string& p_name, const type& p_value )
			{
				if ( !parameters_.insert( std::make_pair( p_name, make_parameter( p_name, boost::lexical_cast< std::string >( p_value ) ) ) ).second )
					throw std::invalid_argument( "error while adding parameter " + p_name + " to execution + " + name_ + " please check configuration" );
				return *this;
			}

			template< typename value_type >
			const value_type execution::parameter( const std::string& parameter_name ) const
			{
				parameter_map::const_iterator i = parameters_.find( parameter_name );
				if ( i == parameters_.end() )
					throw std::logic_error("no such parameter " + parameter_name + " at parameter list :" + type_ + " " + name_ + "( " + algorithm_name_ + " ) ");
				return boost::lexical_cast< value_type >( i->second->value_ );
			}

			typedef boost::shared_ptr< execution > execution_ptr;

			bool operator<( const execution_ptr& first, const execution_ptr& second );
			bool operator==( const execution_ptr& first, const std::string& execution_name );

			execution_ptr make_execution( const std::string& name, const char type, const std::string& algorithm_name );

			typedef std::map< std::string, execution_ptr > execution_list;

			class stock_set : virtual public boost::noncopyable
			{
			public:
				typedef std::set< stsc::common::shared_string > stock_names;
				const stock_names stock_names_;
				execution_list executions_;

				explicit stock_set( const stock_names& names );
				void add_execution( const std::string& execution_name, const execution_ptr& e );
				bool find_execution_name( const std::string& execution_name ) const;
			};

			typedef boost::shared_ptr< stock_set > stock_set_ptr;
			typedef std::vector< stock_set_ptr > stock_sets;
		}
		//
		class algorithm_manager;
		//
		class simulation_configuration : virtual public boost::noncopyable
		{
			friend class algorithm_manager;

			friend void stsc::tests_::engine::simulation_configuration_process_line_tests();
			friend void stsc::tests_::engine::simulation_configuration_process_instrument_list_tests();
			friend void stsc::tests_::engine::simulation_configuration_process_assignment_tests();
			friend void stsc::tests_::engine::simulation_configuration_divide_assignment_line_tests();
			friend void stsc::tests_::engine::simulation_configuration_generate_execution_ptr_tests();

			const common::shared_name_storage& stock_names_;
			details::stock_sets configuration_;
			details::stock_set_ptr current_stock_set_;
			
		public:
			explicit simulation_configuration( const common::shared_name_storage& stock_names );
			~simulation_configuration();
			void clear();
			//
			static const std::string line_index_str_( const size_t line_index );
			void read( std::istream& in );
			//
			static std::string& trim_line_( std::string& line );
			static void check_and_append_next_line_( std::string& line, std::istream& stream, size_t& line_index );
			static bool comment_( const std::string& line );
			static std::string& delete_brackets_from_parameter_value_( std::string& value, char bracket_type, const std::string& execution_name, const std::string& line );
		private:
			void process_line_( const std::string& line, const size_t line_index );
			void process_instrument_list_( const std::string& line, const size_t line_index );
			void process_assignment_( const std::string& line, const size_t line_index );
			void divide_assignment_line_( const std::string& line, const size_t line_index, std::string& execution_name, std::string& algorithm_name, std::string& parameters_str );
			details::execution_ptr generate_execution_ptr_( const std::string& execution_name, const char type, const std::string& algorithm_name, const std::string& parameters_str );
		};
	}
}

#endif // _STSC_ENGINE_SIMULATION_CONFIGURATION_H_
