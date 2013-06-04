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
				typedef std::map< common::shared_string, algorithms_storage::algorithm_ptr > algorithms;
				typedef algorithms::const_iterator const_iterator;
				typedef std::pair< const_iterator, const_iterator > on_stock_algorithm_sequence;
				
				typedef std::map< common::shared_string, algorithms > on_stock_algorithms;

				on_stock_algorithms on_stock_algorithms_;
				algorithms on_bar_algorithms_;
				algorithms on_period_algorithms_;

				explicit executions_stock_group();
				~executions_stock_group();

				void clear();
			};
		};
		class algorithm_manager
		{
			friend class stsc::engine::algorithms_storage::algorithm;

			typedef system_utilities::common::shared_name_storage shared_name_storage;
			shared_name_storage stock_names_;

			typedef details::executions_stock_group::on_stock_algorithm_sequence on_stock_algorithm_sequence;

			typedef std::map< common::shared_string, details::executions_stock_group > data_processors;
			data_processors data_processors_;

		public:
			explicit algorithm_manager();
			virtual ~algorithm_manager();
			//
			void clear();
			//
		};
	}
}

#endif // _STSC_ENGINE_ALGORITHM_MANAGER_H_
