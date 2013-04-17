#ifndef _STSC_ENGINE_ALGORITHMS_STORAGE_ON_PERIOD_ALGORITHM_H_
#define _STSC_ENGINE_ALGORITHMS_STORAGE_ON_PERIOD_ALGORITHM_H_

#include <series_storage/series.h>
#include <algorithms_storage/algorithm_prototype.h>

namespace stsc
{
	namespace engine
	{
		namespace algorithms_storage
		{
			template< typename output_signal_type >
			class on_period_algorithm : public details::algorithm_prototype< common::on_period, output_signal_type >
			{
				typedef typename algorithm_prototype< common::on_period, output_signal_type > typed_algorithm;
			protected:
				typedef typename boost::shared_ptr< series_storage::serie< signal_type > > serie_ptr;
			private:
				serie_ptr serie_;
			protected:
				explicit on_period_algorithm( const std::string& name );
				virtual ~on_period_algorithm();
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
			on_period_algorithm< output_signal_type >::on_period_algorithm( const std::string& name )
				: typed_algorithm( name )
			{
			}
			template< typename output_signal_type >
			on_period_algorithm< output_signal_type >::~on_period_algorithm()
			{
			}
			//
			template< typename output_signal_type >
			void on_period_algorithm< output_signal_type >::register_serie()
			{
				serie_ = serie_prototype();
			}
			//
			template< typename output_signal_type >
			void on_period_algorithm< output_signal_type >::register_signal( const bar_type& b, const signal_type& signal )
			{
				return typed_algorithm::register_signal( b, signal );
			}
			template< typename output_signal_type >
			void on_period_algorithm< output_signal_type >::register_signal( const bar_type& b, signal_type* const signal )
			{
				return typed_algorithm::register_signal( b, signal );
			}
			template< typename output_signal_type >
			void on_period_algorithm< output_signal_type >::register_signal( const bar_type& b, const signal_type_ptr& signal )
			{
				serie_->insert( b.index, signal );
			}
		}
	}
}

#endif // _STSC_ENGINE_ALGORITHMS_STORAGE_ON_PERIOD_ALGORITHM_H_
