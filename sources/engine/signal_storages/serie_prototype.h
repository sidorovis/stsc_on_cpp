#ifndef _STSC_ENGINE_SIGNAL_STORAGES_SERIE_PROTOTYPE_H_
#define _STSC_ENGINE_SIGNAL_STORAGES_SERIE_PROTOTYPE_H_

#include <typeinfo> 

namespace stsc
{
	namespace engine
	{
		namespace details
		{
			template< typename signal_type >
			class serie_prototype
			{
				static const std::type_info& signal_type_info_;
			protected:
				virtual ~serie_prototype()
				{
				}
			private:
				virtual void subscription_check( const std::type_info& ti ) const
				{
					if ( ti != signal_type_info_ )
						throw std::logic_error( std::string("serie signal type with ") + signal_type_info_.name() + " decline subscription on " + ti.name() );
				}
			};
			template< typename signal_type >
			const std::type_info& serie_prototype< signal_type >::signal_type_info_ = typeid( signal_type );
		}
	}
}

#endif // _STSC_ENGINE_SIGNAL_STORAGES_SERIE_PROTOTYPE_H_
