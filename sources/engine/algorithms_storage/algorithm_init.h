#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_INIT_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_INIT_H_

#include <algorithms_storage/algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{

			template< typename init_type >
			struct on_stock_algorithm_init : public details::algorithm_init
			{
				const init_type parameters;
				common::shared_string stock_name;

				explicit on_stock_algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p,
					const common::shared_string& sn );
				explicit on_stock_algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p );
				explicit on_stock_algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m );
			};
			//
			template< typename init_type >
			on_stock_algorithm_init< init_type >::on_stock_algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p,
					const common::shared_string& sn
					)
				: details::algorithm_init( n, m )
				, parameters( p )
				, stock_name( sn )
			{
			}
			//
			template< typename init_type >
			on_stock_algorithm_init< init_type >::on_stock_algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p
					)
				: details::algorithm_init( n, m )
				, parameters( p )
			{
			}
			template< typename init_type >
			on_stock_algorithm_init< init_type >::on_stock_algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m
					)
				: details::algorithm_init( n, m )
				, parameters()
			{
			}
			//
			template< typename init_type >
			struct algorithm_init : public details::algorithm_init
			{
				const init_type parameters;

				explicit algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p,
					const common::shared_string& sn );
				explicit algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p );
				explicit algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m );
			};
			//
			template< typename init_type >
			algorithm_init< init_type >::algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p,
					const common::shared_string& sn
					)
				: details::algorithm_init( n, m )
				, parameters( p )
				, stock_name( sn )
			{
			}
			//
			template< typename init_type >
			algorithm_init< init_type >::algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m,
					const init_type& p
					)
				: details::algorithm_init( n, m )
				, parameters( p )
			{
			}
			template< typename init_type >
			algorithm_init< init_type >::algorithm_init( 
					const common::shared_string& n, 
					const algorithm_manager& m
					)
				: details::algorithm_init( n, m )
				, parameters()
			{
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ALGORITHM_INIT_H_