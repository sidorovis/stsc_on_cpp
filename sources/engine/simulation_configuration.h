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

			template< typename type >
			parameter_ptr make_parameter( const std::string& name, const type& value )
			{
				return parameter_ptr( new parameter( name, value ) );
			}
			//
			typedef std::vector< parameter_ptr > parameter_list;
			//
			class execution
			{
			public:
				const std::string name_;
				const std::string algorithm_name_;
			private:
				parameter_list parameters_;
			public:
				explicit execution( const std::string& name, const std::string& algorithm_name );
				~execution();
				execution& add_parameter( const parameter_ptr& p );
				template< typename type >
				execution& add_parameter( const std::string& p_name, const type& p_value )
				{
					return add_parameter( make_parameter( p_name, boost::lexical_cast< std::string >( p_value ) ) );
				}
				//
				void sort();
				//
				const parameter_list& parameters() const;
			};
			typedef boost::shared_ptr< execution > execution_ptr;

			bool operator<( const execution_ptr& first, const execution_ptr& second );
			bool operator==( const execution_ptr& first, const std::string& execution_name );

			execution_ptr make_execution( const std::string& name, const std::string& algorithm_name );

			typedef std::map< std::string, execution_ptr > execution_list;

			class stock_set : virtual public boost::noncopyable
			{
			public:
				typedef std::set< stsc::common::shared_string > stock_names;
			private:
				const stock_names stock_names_;
				execution_list executions_;
			public:
				explicit stock_set( const stock_names& names );
				void add_execution( const std::string& execution_name, const execution_ptr& e );
				bool find_execution_name( const std::string& execution_name ) const;
			};

			typedef boost::shared_ptr< stock_set > stock_set_ptr;
			typedef std::vector< stock_set_ptr > stock_sets;
		}
		class simulation_configuration : virtual public boost::noncopyable
		{
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
			details::execution_ptr generate_execution_ptr_( const std::string& execution_name, const std::string& algorithm_name, const std::string& parameters_str );
		};
	}
}

#endif // _STSC_ENGINE_SIMULATION_CONFIGURATION_H_
