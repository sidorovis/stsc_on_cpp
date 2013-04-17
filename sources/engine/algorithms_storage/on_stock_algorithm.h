#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ON_STOCK_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ON_STOCK_ALGORITHM_H_

#include <series_storage/series.h>
#include <algorithms_storage/algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			template< typename output_signal_type >
			class on_stock_algorithm : public details::algorithm_prototype< common::on_stock_bar, output_signal_type >
			{
				typedef typename algorithm_prototype< common::on_stock_bar, output_signal_type > typed_algorithm;
			protected:
				typedef typename series_storage::details::on_stock_series_storage< typename signal_type > storage;
				typedef typename storage::serie_ptr serie_ptr;
			private:
				storage storage_;
			protected:
				explicit on_stock_algorithm( const std::string& name );
				virtual ~on_stock_algorithm();
			public:
				/// should be called before process()
				template< typename const_iterator_type >
				void register_stock_list( const_iterator_type from, const_iterator_type to );
			protected:
				virtual void register_signal( const bar_type& b, const signal_type& signal );
				virtual void register_signal( const bar_type& b, signal_type* const signal );
				virtual void register_signal( const bar_type& b, const signal_type_ptr& s );
			private:
				virtual void process( const bar_type& b ) = 0;
				virtual serie_ptr serie_prototype() const = 0;
			};

			template< typename output_signal_type >
			on_stock_algorithm< output_signal_type >::on_stock_algorithm( const std::string& name )
				: typed_algorithm( name )
			{
			}
			template< typename output_signal_type >
			on_stock_algorithm< output_signal_type >::~on_stock_algorithm()
			{
			}
			//
			template< typename output_signal_type >
				template< typename const_iterator_type >
			void on_stock_algorithm< output_signal_type >::register_stock_list( const_iterator_type from, const_iterator_type to )
			{
				for ( const_iterator_type i = from ; i != to ; ++i )
					storage_.series_[ *i ] = serie_prototype();
			}
			template< typename output_signal_type >
			void on_stock_algorithm< output_signal_type >::register_signal( const bar_type& b, const signal_type& signal )
			{
				return typed_algorithm::register_signal( b, signal );
			}
			template< typename output_signal_type >
			void on_stock_algorithm< output_signal_type >::register_signal( const bar_type& b, signal_type* const signal )
			{
				return typed_algorithm::register_signal( b, signal );
			}
			template< typename output_signal_type >
			void on_stock_algorithm< output_signal_type >::register_signal( const bar_type& b, const signal_type_ptr& signal )
			{
				if ( storage_.series_.find( b.stock_name ) == storage_.series_.end() )
					throw std::logic_error( "inserting new stock to on_stock_algorithm, after initialization is deprecated" );
				storage_.series_[ b.stock_name ]->insert( b.index, signal );
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ON_STOCK_ALGORITHM_H_
