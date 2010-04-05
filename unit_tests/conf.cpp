#include "config.h"

#include <boost/test/unit_test.hpp>

struct Fc {
	Fc()
	 : cfg1(), cfg2()
	{
		cfg1.put("a.aa", 10);
		cfg1.put("a.ab", 20);
		cfg1.put("a.ac", 30);
		cfg1.put("b.ba", 100);

		cfg2.put("a.aa", 15);
		cfg2.put("a.ad", 45);
		cfg2.put("c.ca", 99);
	}

	~Fc()
	{
	}

	Config::Node cfg1;
	Config::Node cfg2;
};

BOOST_FIXTURE_TEST_CASE( config_init, Fc )
{
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.aa"), 10 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ab"), 20 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ac"), 30 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("b.ba"), 100 );
}

BOOST_FIXTURE_TEST_CASE( config_set_again, Fc )
{
	cfg1.put("a.aa", 11);
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.aa"), 11 );
}

BOOST_FIXTURE_TEST_CASE( config_merge1, Fc )
{
	Config::merge_into(cfg1, cfg2);
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.aa"), 15 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ab"), 20 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ac"), 30 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ad"), 45 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("b.ba"), 100 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("c.ca"), 99 );
}

BOOST_FIXTURE_TEST_CASE( config_merge_override, Fc )
{
	cfg2.put("a._merge", "override");
	Config::merge_into(cfg1, cfg2);
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.aa"), 15 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ab", 0), 0 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ac", 0), 0 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ad"), 45 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("b.ba"), 100 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("c.ca"), 99 );
}
