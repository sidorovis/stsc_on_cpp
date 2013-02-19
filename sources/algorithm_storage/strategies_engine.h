#ifndef _STSC_ALGORITHM_STORAGE_STRATEGIES_ENGINE_H_
#define _STSC_ALGORITHM_STORAGE_STRATEGIES_ENGINE_H_

#include <boost/noncopyable.hpp>

#include <algorithms/algorithm_prototype.h>

namespace stsc
{
	namespace algorithm_storage
	{

		namespace details
		{
			struct algorithm_storage
			{
				typedef algorithm* const const_pointer;
				typedef std::map< std::string, const_pointer > algorithms;
				algorithms data_;

				template< typename signal_type >
				void insert( algorithm_prototype< signal_type >* const algo )
				{
					data_.insert( std::make_pair( algo->name_, algo ) );
				}
				template< typename signal_type >
				void erase( algorithm_prototype< signal_type >* const algo )
				{
					data_.erase( algo->name_ );
				}
				template< typename signal_type >
				const algorithm_prototype< signal_type >* const subscription_check( const std::string& name ) const
				{
					algorithms::const_iterator i = data_.find( name );
					if ( i == data_.end() )
						throw std::logic_error( "subscription to unknown algorithm '" + name + "'" );
					i->second->subscription_check( typeid( signal_type ) );
					typedef const algorithm_prototype< signal_type >* const pointer;
					pointer algorithm = dynamic_cast< pointer >( i->second );
					if ( !algorithm )
						throw std::logic_error( "subscription to unknown algorithm '" + name + "' type" );
					return algorithm;
				}
				void clear()
				{
					for ( algorithms::iterator i = data_.begin() ; i != data_.end() ; ++i )
						i->second->clear();
				}
			};
		};

		class strategies_engine : protected boost::noncopyable
		{
			details::algorithm_storage algorithms_;
		public:
			explicit strategies_engine();
			~strategies_engine();
			void clear();
			//
			template< typename signal_type >
			void registrate_algorithm( algorithm_prototype< signal_type >* const algorithm )
			{
				algorithms_.insert( algorithm );
			}
			template< typename signal_type >
			void unregister_algorithm( algorithm_prototype< signal_type >* const algorithm )
			{
				algorithms_.erase( algorithm );
			}
			template< typename signal_type >
			const signal_vector< signal_type >& subscribe( const std::string& name )
			{
				return algorithms_.subscription_check< signal_type >( name )->signals();
			}

		};
	}
}

#endif // _STSC_ALGORITHM_STORAGE_STRATEGIES_ENGINE_H_

