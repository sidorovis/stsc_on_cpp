#include <test_registrator.h>

#include <simulation_configuration.h>

using namespace stsc::engine;
using namespace stsc::engine::details;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace
			{
				void simulation_configuration_trim_line_tests_helper( const std::string& in, const std::string& expected )
				{
					std::string test_string;
					test_string = in;
					BOOST_CHECK_EQUAL( simulation_configuration::trim_line_( test_string ), expected );
				}
			}
			void details_parameter_tests()
			{
				parameter_ptr pp;
				BOOST_CHECK_NO_THROW( pp = make_parameter( "hello", "world" ) );
				BOOST_CHECK_EQUAL( pp->name_, "hello" );
				BOOST_CHECK_EQUAL( pp->value_, "world" );
				BOOST_CHECK_NO_THROW( pp = make_parameter( "hello", "15.4" ) );
				BOOST_CHECK_EQUAL( pp->value_, "15.4" );
				BOOST_CHECK_EQUAL( pp->value< double >(), 15.4 );
				BOOST_CHECK_NO_THROW( pp = make_parameter( "hello", 10 ) );
				BOOST_CHECK_EQUAL( pp->value_, "10" );
				BOOST_CHECK_EQUAL( pp->value< int >(), 10 );
			}
			void details_parameter_list_tests()
			{
				BOOST_CHECK_EQUAL( typeid( std::iterator_traits< parameter_list::iterator >::iterator_category ) == typeid( std::random_access_iterator_tag ), true );
				parameter_list list;
				list.push_back( make_parameter( "b", "a" ) );
				list.push_back( make_parameter( "g", "a" ) );
				list.push_back( make_parameter( "u", "a" ) );
				list.push_back( make_parameter( "w", "a" ) );
				list.push_back( make_parameter( "i", "a" ) );

				std::sort( list.begin(), list.end() );

				BOOST_CHECK_EQUAL( list[0]->name_, "b" );
				BOOST_CHECK_EQUAL( list[1]->name_, "g" );
				BOOST_CHECK_EQUAL( list[2]->name_, "i" );
				BOOST_CHECK_EQUAL( list[3]->name_, "u" );
				BOOST_CHECK_EQUAL( list[4]->name_, "w" );
			}
			void details_execution_tests()
			{
				execution_ptr ep;
				BOOST_CHECK_NO_THROW( ep = make_execution( "my super duper algo execution personal name", "algooo" ) );
				BOOST_CHECK_EQUAL( ep->name_, "my super duper algo execution personal name" );
				BOOST_CHECK_EQUAL( ep->algorithm_name_, "algooo" );
				BOOST_CHECK_NO_THROW( ep->add_parameter( "asde", 15 ) );
				BOOST_CHECK_NO_THROW( ep->add_parameter( "asdadsa", "regrg" ) );
				BOOST_CHECK_EQUAL( ep->parameters().size(), 2ul );
				BOOST_CHECK_NO_THROW( ep->sort() );
				BOOST_CHECK_EQUAL( ep->parameters()[0]->name_, "asdadsa" );
				BOOST_CHECK_EQUAL( ep->parameters()[1]->name_, "asde" );
			}
			void details_execution_list_tests()
			{
				BOOST_CHECK_EQUAL( typeid( std::iterator_traits< execution_list::iterator >::iterator_category ) == typeid( std::bidirectional_iterator_tag ), true );

				execution_list list;

				list.insert( std::make_pair( "a1", make_execution( "a1", "ds" ) ) );
			}
			void simulation_configuration_constructor_tests()
			{
				common::shared_name_storage sns;
				BOOST_CHECK_NO_THROW( simulation_configuration sc( sns ) );
			}
			void simulation_configuration_line_index_str_tests()
			{
				BOOST_CHECK_EQUAL( simulation_configuration::line_index_str_( 10ul ), "10" );
				BOOST_CHECK_EQUAL( simulation_configuration::line_index_str_( 134223ul ), "134223" );
			}

			void simulation_configuration_trim_line_tests()
			{
				simulation_configuration_trim_line_tests_helper( " asd ", "asd" );
				simulation_configuration_trim_line_tests_helper( " as er e  re  ergd   ", "as er e  re  ergd" );
				simulation_configuration_trim_line_tests_helper( "    as er e  re  ergd   ", "as er e  re  ergd" );
				simulation_configuration_trim_line_tests_helper( " ewrogjiww   ewrgwerg ", "ewrogjiww   ewrgwerg" );
				simulation_configuration_trim_line_tests_helper( " sde w ergerg \\ ", "sde w ergerg \\" );
				simulation_configuration_trim_line_tests_helper( "[aapl,goog,tuple\\ ", "[aapl,goog,tuple\\" );
				simulation_configuration_trim_line_tests_helper( " #[aapl,goog,tuple\\ ", "#[aapl,goog,tuple\\" );
			}
			void simulation_configuration_check_and_append_next_line_unit_tests()
			{
				common::shared_name_storage sns;
				simulation_configuration sc( sns );
				std::string line;
				size_t line_index = 0;
				{
					std::stringstream ss;
					std::string ll;
					std::getline( ss, ll );
					line = "\\";
					BOOST_CHECK_THROW( sc.check_and_append_next_line_( line, ss, line_index ), std::logic_error );
				}
				{
					std::stringstream ss;
					line = "\\";
					ss << "\\";
					BOOST_CHECK_THROW( sc.check_and_append_next_line_( line, ss, line_index ), std::logic_error );
				}
				{
					std::stringstream ss;
					line = "\\";
					BOOST_CHECK_NO_THROW( sc.check_and_append_next_line_( line, ss, line_index ) );
				}
				{
					std::stringstream ss;
					line = "\\";
					ss << "\\\n\\\n\\\n\\\n\\\n\\\n\\\n";
					BOOST_CHECK_NO_THROW( sc.check_and_append_next_line_( line, ss, line_index ) );
					BOOST_CHECK_EQUAL( line, "" );
				}
				{
					std::stringstream ss;
					line = "# new big comment \\";
					ss << " funny but this comment is multiline to \\ " << std::endl;
					ss << " finishing this comment " << std::endl;
					BOOST_CHECK_NO_THROW( sc.check_and_append_next_line_( line, ss, line_index ) );
					BOOST_CHECK_EQUAL( line, "# new big comment funny but this comment is multiline to finishing this comment" );
				}
			}
			void simulation_configuration_comment_tests()
			{
				BOOST_CHECK_EQUAL( simulation_configuration::comment_( "# comment line" ), true );
				BOOST_CHECK_EQUAL( simulation_configuration::comment_( "non comment line" ), false );
			}
			void simulation_configuration_delete_brackets_from_parameter_value_tests()
			{
				std::string value = "";
				BOOST_CHECK_NO_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '"', "", "" ) );
				value = "\"\"";
				BOOST_CHECK_NO_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '"', "", "" ) );
				value = "''";
				BOOST_CHECK_NO_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '\'', "", "" ) );
				BOOST_CHECK_EQUAL( value, "" );
				value = "' hello worldwj epwjig '";
				BOOST_CHECK_NO_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '\'', "", "" ) );
				BOOST_CHECK_EQUAL( value, " hello worldwj epwjig " );
				value = "\"54g)Uhh;.!@#^%$())pohjf398h(G^\"'''\" 45 45h\"";
				BOOST_CHECK_NO_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '"', "", "" ) );
				BOOST_CHECK_EQUAL( value, "54g)Uhh;.!@#^%$())pohjf398h(G^\"'''\" 45 45h" );
				value = "'f4e545\"";
				BOOST_CHECK_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '\'', "", "" ), std::exception );
				value = "\"th56 erg45'";
				BOOST_CHECK_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '"', "", "" ), std::exception );
				value = "\"5yh546y";
				BOOST_CHECK_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '"', "", "" ), std::exception );
				value = "\'5yh546y";
				BOOST_CHECK_THROW( simulation_configuration::delete_brackets_from_parameter_value_( value, '\'', "", "" ), std::exception );
			}
			void simulation_configuration_process_instrument_list_tests()
			{
				common::shared_name_storage sns;
				sns << "aapl" << "goog" << "ibm";
				simulation_configuration sc( sns );
				BOOST_CHECK_THROW( sc.process_instrument_list_( " [aapl]", 1 ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.process_instrument_list_( "[aapl] ", 1 ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.process_instrument_list_( "[goog2] ", 1 ), std::logic_error );
				BOOST_CHECK_THROW( sc.process_instrument_list_( "[goog,shmug] ", 1 ), std::logic_error );
				BOOST_CHECK_THROW( sc.process_instrument_list_( "", 1 ), std::logic_error );

				BOOST_CHECK_EQUAL( sc.current_stock_set_.get() == NULL, true );
				BOOST_CHECK_NO_THROW( sc.process_instrument_list_( "[aapl,goog,ibm]", 1 ) );
				BOOST_CHECK_EQUAL( sc.current_stock_set_.get() == NULL, false );
				BOOST_CHECK_NO_THROW( sc.process_instrument_list_( "[goog,ibm]", 1 ) );
				BOOST_CHECK_EQUAL( sc.current_stock_set_.get() == NULL, false );
				BOOST_CHECK_EQUAL( sc.configuration_.empty(), false );
				BOOST_CHECK_EQUAL( sc.configuration_.size(), 1ul );
				BOOST_CHECK_NO_THROW( sc.process_instrument_list_( "[goog,ibm,aapl]", 1 ) );
				BOOST_CHECK_EQUAL( sc.configuration_.size(), 2ul );
			}
			void simulation_configuration_divide_assignment_line_tests()
			{
				common::shared_name_storage sns;
				simulation_configuration sc( sns );
				std::string execution_name, algorithm_name, parameters_str;
				BOOST_CHECK_NO_THROW( sc.divide_assignment_line_( "| i = a()", 1, execution_name, algorithm_name, parameters_str ) );
				BOOST_CHECK_NO_THROW( sc.divide_assignment_line_( "| 1i = 1a()", 1, execution_name, algorithm_name, parameters_str ) );
				BOOST_CHECK_NO_THROW( sc.divide_assignment_line_( "| 1i_d = 1a_54()", 1, execution_name, algorithm_name, parameters_str ) );
				BOOST_CHECK_NO_THROW( sc.divide_assignment_line_( "| 1i_dT4 = 1a_54Bs( a1s 2D4. ,='\" 5fr dw )", 1, execution_name, algorithm_name, parameters_str ) );
				BOOST_CHECK_EQUAL( execution_name, "1i_dT4" );
				BOOST_CHECK_EQUAL( algorithm_name, "1a_54Bs" );
				BOOST_CHECK_EQUAL( parameters_str, " a1s 2D4. ,='\" 5fr dw " );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg = ", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg = greg", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| f.erg = greg()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| f,erg = greg()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg erg= greg()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg =erg greg()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg = gr,eg()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg = gre.g()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg = greg\"ewfewf()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.divide_assignment_line_( "| ferg = greg'ewfewf()", 1, execution_name, algorithm_name, parameters_str ), std::invalid_argument );
			}
			void simulation_configuration_generate_execution_ptr_tests()
			{
				common::shared_name_storage sns;
				simulation_configuration sc( sns );
				BOOST_CHECK_NO_THROW( sc.generate_execution_ptr_( "en", "an", "" ) );
				BOOST_CHECK_NO_THROW( sc.generate_execution_ptr_( "en", "an", " a =1 ,v = 5.546 , gf = \"ergeg\", ytjy = 'erger', rt45 = \"e2 rger\" " ) );
				details::execution_ptr ex = sc.generate_execution_ptr_( "en", "an", " a =1 ,v = 5.546 , gf = \"ergeg\", ytjy = 'erger', rt45 = \"e2 rger\" " );
				ex->sort();
				BOOST_CHECK_EQUAL( ex->parameters().size(), 5ul );
				BOOST_CHECK_EQUAL( ex->parameters()[0]->name_, "a" );
				BOOST_CHECK_EQUAL( ex->parameters()[0]->value< int >(), 1 );
				BOOST_CHECK_EQUAL( ex->parameters()[1]->name_, "gf" );
				BOOST_CHECK_EQUAL( ex->parameters()[1]->value< std::string >(), "ergeg" );
				BOOST_CHECK_EQUAL( ex->parameters()[2]->name_, "rt45" );
				BOOST_CHECK_EQUAL( ex->parameters()[2]->value< std::string >(), "e2 rger" );
				BOOST_CHECK_EQUAL( ex->parameters()[3]->name_, "v" );
				BOOST_CHECK_EQUAL( ex->parameters()[3]->value< double >(), 5.546 );
				BOOST_CHECK_EQUAL( ex->parameters()[4]->name_, "ytjy" );
				BOOST_CHECK_EQUAL( ex->parameters()[4]->value< std::string >(), "erger" );
			}
			void simulation_configuration_process_assignment_tests()
			{
				common::shared_name_storage sns;
				sns << "aapl" << "goog" << "ibm";
				simulation_configuration sc( sns );

				BOOST_CHECK_THROW( sc.process_assignment_( "", 1 ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.process_assignment_( " | a = e()", 1 ), std::invalid_argument );
				
				BOOST_CHECK_THROW( sc.process_assignment_( "| i = a()", 1 ), std::logic_error );
			}
			void simulation_configuration_process_line_tests()
			{
				common::shared_name_storage sns;
				sns << "aapl" << "goog" << "ibm";
				simulation_configuration sc( sns );
				BOOST_CHECK_NO_THROW( sc.process_line_( "[aapl ,ibm]", 1 ) );
				BOOST_CHECK_NO_THROW( sc.process_line_( "| a1 = exe( h1 = '234', h5 = 543 )", 1 ) );
				BOOST_CHECK_NO_THROW( sc.process_line_( "| a2 = exe( h1 = '234', h5 = 543, a1 )", 1 ) );
				BOOST_CHECK_THROW( sc.process_line_( "| a2 = exe()", 1 ), std::logic_error );
				BOOST_CHECK_THROW( sc.process_line_( "| a3 = exe( a4 )", 1 ), std::invalid_argument );
				BOOST_CHECK_THROW( sc.process_line_( " a1 = exe( h1 = '234', h5 = 543 )", 1 ), std::logic_error );
			}
			void simulation_configuration_read_unit_tests()
			{
				common::shared_name_storage sns;
				sns << "aapl" << "goog" << "ibm";
				simulation_configuration sc( sns );
				{
					std::stringstream ss;
					ss << "[aapl, goog, ibm]" << std::endl;
					ss << "| a1 = e1( p1 = 123, p2 = '343452', p3 = 354.765 )" << std::endl;
					ss << "| a2 = e2( v1 = \"qewd\", v2 = 345, v3 = hello world \\" << std::endl;
					ss << "new child hood\" yeeeey )" << std::endl;
					ss << "# | a2 = e2( v1 = \"qewd\", v2 = 345, v3 = hello world )" << std::endl;
					ss << "| a3 = e3( s1 = 'ergwerg 45t4\"t45', s2 = 54.6425, s3 = lockway, a2 )" << std::endl;
					BOOST_CHECK_NO_THROW( sc.read( ss ) );
				}
			}
		}
	}
}
