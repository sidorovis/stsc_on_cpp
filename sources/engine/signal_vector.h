#ifndef _STSC_ENGINE_SIGNAL_VECTOR_H_
#define _STSC_ENGINE_SIGNAL_VECTOR_H_

#include <map>
#include <stdexcept>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <bar_types.h>

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			void signal_vector_unit_tests();
		}
	}

	namespace engine
	{
		namespace details
		{
			struct signals_storage;
		}

		// signal_vector< type > template is a way to store signals from algorithms
		// notice that signal_vector< type > clear memory after signals by itself, please just send here pointers to your data
		// for example: 
		// signal_vector< double > sv;
		// sv.insert( common::bar_type(), new double( 1.5 ) );
		// Attention: !!! NEVER delete memory that you send to signal_vector it will terminate the application

		class data_vector
		{
			friend struct details::signals_storage;
		protected:
			virtual ~data_vector();
		private:
			virtual void subscription_check( const std::type_info& ti ) const = 0;
		};

		namespace details
		{
			template< typename signal_type >
			struct signal_map : boost::noncopyable
			{
				typedef boost::shared_ptr< const signal_type > signal_type_ptr;
				typedef std::map< const common::bar_type* const, const signal_type_ptr > map;
				map map_;
			public:
				explicit signal_map()
				{
				}
				~signal_map()
				{
					clear();
				}
				void clear()
				{
					map_.clear();
				}
			};
		};

		template< typename type >
		class signal_vector : public data_vector
		{
			friend void stsc::tests_::engine::signal_vector_unit_tests();
			friend struct details::signals_storage;
		public:
			typedef type signal_type;
			typedef const type* const pointer;
		private:
			typedef details::signal_map< signal_type > typed_signal_map;
			typedef boost::shared_ptr< typed_signal_map > signal_map_ptr;

			static const std::type_info& signal_type_info_;
			signal_map_ptr signals_map_;

		protected:
			explicit signal_vector()
				: signals_map_( new typed_signal_map() )
			{
			}
		private:
			void operator=( const signal_vector<type>& );
		public:
			signal_vector( const signal_vector< type >& copy )
				: signals_map_( copy.signals_map_ )
			{
			}
			virtual ~signal_vector()
			{
			}
			//
			void clear()
			{
				signals_map_->clear();
			};
			void insert( const common::bar_type* bar, const signal_type* data )
			{
				if ( !( signals_map_->map_.insert( std::make_pair( bar, typed_signal_map::signal_type_ptr( data ) ) ).second ) )
					throw std::logic_error( "impossible to add to signal on single bar" );
			}
			const signal_type* at( const common::bar_type* bar ) const 
			{
				typename typed_signal_map::map::const_iterator i = signals_map_->map_.find( bar );
				if ( i == signals_map_->map_.end() )
					return NULL;
				return &(*(i->second));
			}
			//
		private:
			virtual void subscription_check( const std::type_info& ti ) const
			{
				if ( ti != signal_type_info_ )
					throw std::logic_error( std::string("signal_vector with ") + signal_type_info_.name() + " decline subscription on " + ti.name() );
			}
		};
		template< typename type >
		const std::type_info& signal_vector< type >::signal_type_info_ = typeid( signal_type );
	}
}

#endif // _STSC_ENGINE_SIGNAL_VECTOR_H_
