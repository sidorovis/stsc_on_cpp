#ifndef _STSC_ENGINE_SIGNALS_STORAGE_H_
#define _STSC_ENGINE_SIGNALS_STORAGE_H_

#include <string>

#include <boost/noncopyable.hpp>

#include <signal_vector.h>

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			struct signals_storage : public boost::noncopyable
			{
				typedef boost::shared_ptr< data_vector > data_vector_ptr;
				typedef std::map< std::string, data_vector_ptr > vectors;
				vectors data_;

				~signals_storage();

				template< typename output_signal_type >
				signal_vector< output_signal_type >& create_vector( const std::string& name )
				{
					typedef signal_vector< output_signal_type > vector;
					std::pair< vectors::iterator, bool > res = data_.insert( std::make_pair( name, data_vector_ptr( new vector() ) ) );
					if ( res.second )
						return dynamic_cast< vector& >( *(res.first->second.get()) );
					throw std::logic_error( "signal_vector '" + name + "' exist" );
				}
				void destroy_vector( const std::string& name );
				//
				template< typename output_signal_type >
				const signal_vector< output_signal_type >& subscribe( const std::string& name ) const
				{
					vectors::const_iterator i = data_.find( name );
					if ( i == data_.end() )
						throw std::logic_error( "subscription to unknown signal_vector '" + name + "'" );
					i->second->subscription_check( typeid( output_signal_type ) );
					typedef const signal_vector< output_signal_type >* const reference;
					reference vector = dynamic_cast< reference >( i->second.get() );
					if ( !vector )
						throw std::logic_error( "subscription to unknown signal_vector '" + name + "' type" );
					return *vector;
				}
			};
			std::ostream& operator<<( std::ostream& out, const signals_storage& as );
		}
	}
}


#endif // _STSC_ENGINE_SIGNALS_STORAGE_H_

