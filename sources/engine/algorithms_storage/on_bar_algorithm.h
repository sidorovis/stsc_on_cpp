#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ON_BAR_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ON_BAR_ALGORITHM_H_

#include <series_storage/on_bar_serie.h>
#include <algorithms_storage/algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			template< typename output_signal_type >
			class on_bar_algorithm : public details::algorithm_prototype< common::on_bar, output_signal_type >
			{
				typedef typename algorithm_prototype< common::on_bar, signal_type > typed_algorithm;
			protected:
				typedef typename series_storage::details::on_bar_serie< signal_type > serie_type;
				typedef typename serie_type::serie_ptr serie_ptr;
			private:
				serie_type storage_;
			protected:
				explicit on_bar_algorithm( const std::string& name );
				virtual ~on_bar_algorithm();
			public:
				/// should be called before process()
				void register_serie();
			protected:
				virtual void register_signal( const bar_type& b, const signal_type& signal );
				virtual void register_signal( const bar_type& b, signal_type* const signal );
				virtual void register_signal( const bar_type& b, const signal_type_ptr& s );
			private:
				virtual void process( const bar_type& b ) = 0;
				virtual serie_ptr serie_prototype() const = 0;
			};

			template< typename output_signal_type >
			on_bar_algorithm< output_signal_type >::on_bar_algorithm( const std::string& name )
				: typed_algorithm( name )
			{
			}
			template< typename output_signal_type >
			on_bar_algorithm< output_signal_type >::~on_bar_algorithm()
			{
			}
			//
			template< typename output_signal_type >
			void on_bar_algorithm< output_signal_type >::register_serie()
			{
				storage_.serie_ = serie_prototype();
			}
			//
			template< typename output_signal_type >
			void on_bar_algorithm< output_signal_type >::register_signal( const bar_type& b, const signal_type& signal )
			{
				return typed_algorithm::register_signal( b, signal );
			}
			template< typename output_signal_type >
			void on_bar_algorithm< output_signal_type >::register_signal( const bar_type& b, signal_type* const signal )
			{
				return typed_algorithm::register_signal( b, signal );
			}
			template< typename output_signal_type >
			void on_bar_algorithm< output_signal_type >::register_signal( const bar_type& b, const signal_type_ptr& signal )
			{
				storage_.serie_->insert( b.index, signal );
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ON_BAR_ALGORITHM_H_
