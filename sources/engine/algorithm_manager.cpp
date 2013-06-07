#include <algorithm_manager.h>

#include <algorithms_storage/on_stock_algorithm.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			executions_stock_group::executions_stock_group()
			{
			}
			executions_stock_group::~executions_stock_group()
			{
			}
			void executions_stock_group::clear()
			{
				on_period_algorithms_.clear();
				on_bar_algorithms_.clear();
				on_stock_algorithms_.clear();
			}
		}
		//
		algorithm_manager::algorithm_manager()
		{
		}
		algorithm_manager::~algorithm_manager()
		{
		}

		void algorithm_manager::prepare( const simulation_configuration& simulation )
		{
			for( details::stock_sets::const_iterator i = simulation.configuration_.begin() ; i != simulation.configuration_.end() ; ++i )
			{
				executions_stock_group_ptr ptr( new details::executions_stock_group() );
				
				for( details::stock_set::stock_names::const_iterator u = (*i)->stock_names_.begin(); u != (*i)->stock_names_.end() ; ++u )
					data_processors_.insert( std::make_pair( (*u), ptr ) );

				for( details::execution_list::const_iterator u = (*i)->executions_.begin() ; u != (*i)->executions_.end() ; ++u )
				{
					u->first; // execution name
					u->second->algorithm_name_; // algorithm_name
					u->second->type_; // type
					const details::parameter_map& pl = u->second->parameters();

					switch ( u->second->type_ )
					{
					case details::execution::STOCK :

//						algorithms_storage::typed_algorithm< on_stock_algorithm > ptr = algorithm_storage().create_on_stock( u->second->algorithm_name_ );

						break;
					case details::execution::BAR :
						break;
					case details::execution::PERIOD :
						break;
					default:
						throw std::logic_error( std::string( "unknown algorithm type: " ) + u->second->type_ + " on " + u->first + " execution" );
					}

				}
			}
		}

		void algorithm_manager::clear()
		{
			data_processors_.clear();
		}
	}
}
