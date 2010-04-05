#include "config.h"
#include "exception.h"

#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

BOOST_AUTO_TEST_CASE(test_empty_config)
{
	Config::Node n = Config::Node();
	BOOST_CHECK(n.empty());
}

BOOST_AUTO_TEST_CASE(test_default_config)
{
	Config::Node n = Config::Default();
	BOOST_CHECK(!n.empty());
}

BOOST_AUTO_TEST_CASE(test_nonexistant_config)
{
	BOOST_CHECK_THROW(
		Config::Node n = Config::get_library_config("nonexistant97yh(*^$4u678"),
		TokenizerLibError
		);
}



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

namespace {
template<typename T>
std::vector<T> all_values(const Config::Node& c, const std::string& key)
{
	std::vector<T> vec;
	BOOST_FOREACH (const Config::Node::value_type &v, c) {
		if (v.first == key) {
			vec.push_back(v.second.get_value<T>());
		}
	}
	return vec;
}
}

struct Fc2 {
	Fc2()
	 : c1(), c2()
	{
		c1.put("a.aa", 10);
		std::pair<std::string, Config::Node> p;
		p.first = "aa";
		p.second.put_value(20);
		c1.get_child("a").push_back(p);
		p.second.put_value(30);
		c1.get_child("a").push_back(p);
		c2.put("a._merge", "override");
		c2.put("a.aa", 15);
		c2.put("a.ad", 45);
	}

	~Fc2()
	{
	}

	Config::Node c1;
	Config::Node c2;
};

BOOST_FIXTURE_TEST_CASE( config_dup, Fc2 )
{
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	std::vector<int> va = all_values<int>(c1.get_child("a"), "aa");

	BOOST_CHECK_EQUAL_COLLECTIONS( v.begin(), v.end(), va.begin(), va.end() );
}

BOOST_FIXTURE_TEST_CASE( config_dup_merge, Fc2 )
{
	Config::Node m = Config::merge_copy(c1, c2);
	std::vector<int> v;
	v.push_back(15);
	std::vector<int> va = all_values<int>(m.get_child("a"), "aa");

	BOOST_CHECK_EQUAL_COLLECTIONS( v.begin(), v.end(), va.begin(), va.end() );
}

BOOST_FIXTURE_TEST_CASE( config_dup_merge_dup, Fc2 )
{
	std::pair<std::string, Config::Node> p;
	p.first = "aa";
	p.second.put_value(25);
	c2.get_child("a").push_back(p);
	Config::Node m = Config::merge_copy(c1, c2);
	std::vector<int> v;
	v.push_back(15);
	v.push_back(25);
	std::vector<int> va = all_values<int>(m.get_child("a"), "aa");
	BOOST_CHECK_EQUAL_COLLECTIONS( v.begin(), v.end(), va.begin(), va.end() );
}
