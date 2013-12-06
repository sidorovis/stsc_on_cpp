#ifndef _STSC_ENGINE_ALGORITHM_MANAGER_H_
#define _STSC_ENGINE_ALGORITHM_MANAGER_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <shared_name_storage.h>

#include <algorithm_storage.h>

#include <algorithms_storage/algorithm.h>

#include <simulation_configuration.h>


namespace stsc
{
	namespace engine
	{
		namespace details
		{
			struct executions_stock_group
			{

				typedef algorithms_storage::algorithm_interface< common::on_stock_bar > on_stock_algorithm;
				typedef algorithms_storage::algorithm_interface< common::on_bar > on_bar_algorithm;
				typedef algorithms_storage::algorithm_interface< common::on_period > on_period_algorithm;

				
				typedef std::map< common::shared_string, on_stock_algorithm > stocked_algorithms;
				typedef std::map< common::shared_string, stocked_algorithms > on_stock_algorithms;

				typedef std::map< common::shared_string, on_bar_algorithm > on_bar_algorithms;
				typedef std::map< common::shared_string, on_period_algorithm > on_period_algorithms;

				on_stock_algorithms on_stock_algorithms_;
				on_bar_algorithms on_bar_algorithms_;
				on_period_algorithms on_period_algorithms_;

				explicit executions_stock_group();
				~executions_stock_group();

				void clear();
			};
		};
		class algorithm_manager
		{
			friend class stsc::engine::algorithms_storage::algorithm;

			typedef details::executions_stock_group::on_stock_algorithm_sequence on_stock_algorithm_sequence;

			typedef boost::shared_ptr< details::executions_stock_group > executions_stock_group_ptr;

			typedef std::multimap< common::shared_string, executions_stock_group_ptr > data_processors;
			data_processors data_processors_;

		public:
			explicit algorithm_manager();
			virtual ~algorithm_manager();
			//
			void prepare( const simulation_configuration& configuration );
			void clear();
			//
		};
	}
}

#endif // _STSC_ENGINE_ALGORITHM_MANAGER_H_
