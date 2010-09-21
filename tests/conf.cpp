/*
    Copyright (C) 2010 Tomasz Śniatowski, Adam Radziszewski
    Part of the libtoki project

    This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option)
any later version.

    This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. 

    See the LICENSE and COPYING files for more details.
*/

#include <libtoki/util/settings.h>
#include <libtoki/exception.h>
#include <libpwrutils/foreach.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( config )

BOOST_AUTO_TEST_CASE(test_empty_config)
{
	Toki::Config::Node n = Toki::Config::Node();
	BOOST_CHECK(n.empty());
}

BOOST_AUTO_TEST_CASE(test_default_config_config)
{
	BOOST_CHECK_NO_THROW(
		Toki::Config::Node n = Toki::default_config();
		BOOST_CHECK(!n.empty());
	);
}

BOOST_AUTO_TEST_CASE(test_default_config_config_fail)
{
	{
		PwrNlp::ConfigPathSetter l(Toki::Path::Instance(), "nonexistant9427398yq564657^%&");
		BOOST_CHECK_THROW(
			Toki::Config::Node n = Toki::default_config(),
			Toki::Error
		);
	}
	BOOST_CHECK_NO_THROW(
		Toki::Config::Node n = Toki::default_config();
		BOOST_CHECK(!n.empty());
	);
}

BOOST_AUTO_TEST_CASE(test_nonexistant_config)
{
	BOOST_CHECK_THROW(
		Toki::Config::Node n = Toki::get_named_config("nonexistant97yh(*^$4u678"),
		Toki::Error
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

	Toki::Config::Node cfg1;
	Toki::Config::Node cfg2;
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
	Toki::Config::merge_into(cfg1, cfg2);
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
	Toki::Config::merge_into(cfg1, cfg2);
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.aa"), 15 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ab", 0), 0 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ac", 0), 0 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("a.ad"), 45 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("b.ba"), 100 );
	BOOST_CHECK_EQUAL( cfg1.get<int>("c.ca"), 99 );
}

namespace {
template<typename T>
std::vector<T> all_values(const Toki::Config::Node& c, const std::string& key)
{
	std::vector<T> vec;
	foreach (const Toki::Config::Node::value_type &v, c) {
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
		std::pair<std::string, Toki::Config::Node> p;
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

	Toki::Config::Node c1;
	Toki::Config::Node c2;
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
	Toki::Config::Node m = Toki::Config::merge_copy(c1, c2);
	std::vector<int> v;
	v.push_back(15);
	std::vector<int> va = all_values<int>(m.get_child("a"), "aa");

	BOOST_CHECK_EQUAL_COLLECTIONS( v.begin(), v.end(), va.begin(), va.end() );
}

BOOST_FIXTURE_TEST_CASE( config_dup_merge_dup, Fc2 )
{
	std::pair<std::string, Toki::Config::Node> p;
	p.first = "aa";
	p.second.put_value(25);
	c2.get_child("a").push_back(p);
	Toki::Config::Node m = Toki::Config::merge_copy(c1, c2);
	std::vector<int> v;
	v.push_back(15);
	v.push_back(25);
	std::vector<int> va = all_values<int>(m.get_child("a"), "aa");
	BOOST_CHECK_EQUAL_COLLECTIONS( v.begin(), v.end(), va.begin(), va.end() );
}

BOOST_AUTO_TEST_SUITE_END()
