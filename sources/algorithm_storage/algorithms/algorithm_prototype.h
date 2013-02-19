#ifndef _STSC_ALGORITHM_STORAGE_ALGORITHM_ALGORITHM_PROTOTYPE_H_
#define _STSC_ALGORITHM_STORAGE_ALGORITHM_ALGORITHM_PROTOTYPE_H_

#include <string>
#include <boost/noncopyable.hpp>

#include <bar_types.h>

#include <signal_vector.h>

namespace stsc
{
	namespace algorithm_storage
	{
		// algorithm_prototype is a template for algorithms
		// please inherit algorithm_prototype (at least algorithm_prototype< void >) to create correct algortihms
		// Attention, never delete signals that where created by algortihm, storage should delete it automatically
		// see tests/algorithm_storage_tests/algorithm_examples.h to see algortihm examples

		namespace details
		{
			struct algorithm_storage;
		}
		class strategies_engine;

		class algorithm
		{
			friend struct details::algorithm_storage;
		public:
			virtual ~algorithm();
		private:
			virtual void subscription_check( const std::type_info& ti ) const = 0;
			virtual void clear() = 0;
		};

		template< typename signal_type >
		class algorithm_prototype : public algorithm
		{
			friend struct details::algorithm_storage;
		public:
			typedef signal_type output_signal_type;
		private:
			static const std::type_info& signal_type_info_;
			const std::string name_;
			strategies_engine& strategies_engine_;

			signal_vector< signal_type > signals_;

		protected:

			explicit algorithm_prototype( const std::string& name, strategies_engine& se )
				: name_( name )
				, strategies_engine_( se )
			{
				strategies_engine_.registrate_algorithm< signal_type >( this );
			}
			virtual ~algorithm_prototype()
			{
				strategies_engine_.unregister_algorithm< signal_type >( this );
			}
		private:
			virtual void process( const common::bar_type& b ) = 0;
			
			virtual void subscription_check( const std::type_info& ti ) const
			{
				if ( ti != signal_type_info_ )
					throw std::logic_error( "algorithm " + name_ + " decline subscription on " + ti.name() );
			}
			virtual void clear()
			{
				signals_.clear();
			}
		protected:
			void registrate_signal( const common::bar_type& b, output_signal_type* const output_signal )
			{
				signals_.insert( b, output_signal );
			}
		public:
			const signal_vector< signal_type >& signals() const
			{
				return signals_;
			}
		};
		template< typename signal_type >
		const std::type_info& algorithm_prototype< signal_type >::signal_type_info_ = typeid( signal_type );
	}
}

#endif // _STSC_ALGORITHM_STORAGE_ALGORITHM_ALGORITHM_PROTOTYPE_H_
