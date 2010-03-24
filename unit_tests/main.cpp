//#define BOOST_TEST_MODULE master
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( my_test )
{
	int a = 0;
	BOOST_CHECK( a == 0 );
}
