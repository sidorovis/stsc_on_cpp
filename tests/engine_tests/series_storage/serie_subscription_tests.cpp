#include <test_registrator.h>

#include <series_storage/serie_subscription.h>

using namespace stsc::engine::series_storage;

namespace stsc
{
	namespace tests_
	{
		namespace engine
		{
			namespace series_storage
			{

				namespace 
				{
					class serie_subscription_test_helper : public serie_subscription< float >
					{
						signal_type for_return_;
					public:
						explicit serie_subscription_test_helper(){}
						~serie_subscription_test_helper(){}
						//
						const signal_type& at( const common::index key ) const
						{
							return for_return_;
						}
						const signal_type_const_ptr ptr_at( const common::index key ) const
						{
							return signal_type_const_ptr();
						}
						const size_t size() const
						{
							return 0ul;
						}
						const bool empty() const
						{
							return true;
						}
					};
				}

				void serie_subscription_unit_tests()
				{
					serie_subscription_test_helper ssth;
					BOOST_CHECK_NO_THROW( ssth.subscription_check( typeid( int ) ) );
					BOOST_CHECK_NO_THROW( ssth.at( common::index( 4 ) ) );
					BOOST_CHECK_NO_THROW( ssth.ptr_at( common::index( 4 ) ) );
					BOOST_CHECK_NO_THROW( ssth.size() );
					BOOST_CHECK_NO_THROW( ssth.empty() );
				}
			}
		}
	}
}

