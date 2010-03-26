//#define BOOST_TEST_MODULE master
#include <boost/test/included/unit_test.hpp>
#include "compare.h"

BOOST_AUTO_TEST_CASE(test_test)
{
	int a = 0;
	BOOST_CHECK(a == 0);
}

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	boost::unit_test::test_suite* ts1 = BOOST_TEST_SUITE("compare");
	init_compare_suite(ts1);
	boost::unit_test::framework::master_test_suite().add(ts1);
	return 0;
}
