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

#include <libtoki/srx/util.h>
#include <libtoki/srx/document.h>
#include <libtoki/srx/segmenter.h>
#include <libtoki/srx/srx.h>
#include <libtoki/layertokenizer.h>
#include <libtoki/unicodeicustringwrapper.h>

#include <fstream>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

namespace {

#ifdef LIBTOKI_TEST_DATA_DIR
	static std::string data_dir = LIBTOKI_TEST_DATA_DIR;
#else
	static std::string data_dir = "./";
#endif

}


BOOST_AUTO_TEST_SUITE( srx );

BOOST_AUTO_TEST_CASE( unquote )
{

	std::string s1 = "asdlkh\\asjkd\\.asd+{}\\alh\\\\asd21\\a";
	std::string s1u = Toki::Srx::Util::unquote_regex(s1);
	BOOST_CHECK_EQUAL( s1, s1u );
	std::string s2 = "as\\Q.!abcd\\E.";
	BOOST_CHECK_EQUAL( "as\\.!abcd.", Toki::Srx::Util::unquote_regex(s2) );
	std::string s3 = "Characters that must be quoted to be treated as literals "
					 "\nare \\Q* ? + [ ( ) { } ^ $ | \\ . /\\E";
	std::string s3c ="Characters that must be quoted to be treated as literals "
					 "\nare \\* \\? \\+ \\[ \\( \\) \\{ \\} \\^ \\$ \\| \\\\ \\. \\/";
	BOOST_CHECK_EQUAL( s3c, Toki::Srx::Util::unquote_regex(s3) );
}

BOOST_AUTO_TEST_CASE( finitize )
{
	return;
	std::string s00 = "a*";
	BOOST_CHECK_EQUAL("a{0,9}", Toki::Srx::Util::prepare_regex_for_lookbehind(s00, 9));
	std::string s01 = "a\\*";
	BOOST_CHECK_EQUAL("a\\*", Toki::Srx::Util::prepare_regex_for_lookbehind(s01, 9));
	std::string s02 = "a\\\\*";
	BOOST_CHECK_EQUAL("a\\\\{0,9}", Toki::Srx::Util::prepare_regex_for_lookbehind(s02, 9));
	std::string s03 = "a\\\\\\*";
	BOOST_CHECK_EQUAL("a\\\\\\*", Toki::Srx::Util::prepare_regex_for_lookbehind(s03, 9));
	std::string s04 = "a\\\\\\\\*";
	BOOST_CHECK_EQUAL("a\\\\\\\\{0,9}", Toki::Srx::Util::prepare_regex_for_lookbehind(s04, 9));

	std::string ss1 = "a+b*c{10,}";
	BOOST_CHECK_EQUAL("a{1,99}b{0,99}c{10,99}", Toki::Srx::Util::prepare_regex_for_lookbehind(ss1, 99));
}

BOOST_AUTO_TEST_CASE( parse )
{
	Toki::Srx::Document d;
	std::string s = data_dir + "/one.srx";
	std::ifstream ifs(s.c_str());
	d.load(ifs);
	std::vector<Toki::Srx::Rule> rules = d.get_all_rules();
	BOOST_CHECK_EQUAL(rules.size(), 2);
}

namespace {
	//                      0000000000111111111122222222223333333333444444444455555555556666666666
	//                      0123456789012345678901234567890123456789012345678901234567890123456789
	static std::string t = "Mr. Holmes is from the U.K. not from the U.S.A. Is Dr. Watson from there too?";
	int tb[2] = {3, 54};
	int* tbe = tb + 2;
}


BOOST_AUTO_TEST_CASE( simple )
{
	Toki::Srx::Document d;
	std::string s = data_dir + "/one.srx";
	std::ifstream ifs(s.c_str());
	d.load(ifs);
	Toki::Srx::NaiveIcuSegmenter proc;
	proc.load_rules(d.get_all_rules());

	proc.compute_breaks(UnicodeString::fromUTF8(t), 0, t.size());
	std::vector<int> breaks = proc.get_break_positions();

	BOOST_CHECK_EQUAL_COLLECTIONS(tb, tbe, breaks.begin(), breaks.end());

	Toki::Srx::NaiveBoostSegmenter boo;
	boo.load_rules(d.get_all_rules());

	boo.compute_breaks(UnicodeString::fromUTF8(t), 0, t.size());
	breaks = boo.get_break_positions();

	BOOST_CHECK_EQUAL_COLLECTIONS(tb, tbe, breaks.begin(), breaks.end());

	Toki::Srx::HxoIcuSegmenter hxo;
	hxo.load_rules(d.get_all_rules());

	hxo.compute_breaks(UnicodeString::fromUTF8(t), 0, t.size());
	breaks = hxo.get_break_positions();

	BOOST_CHECK_EQUAL_COLLECTIONS(tb, tbe, breaks.begin(), breaks.end());
}

BOOST_AUTO_TEST_CASE( variable_window )
{
	Toki::Srx::Document d;
	std::string s = data_dir + "/one.srx";
	std::ifstream ifs(s.c_str());
	d.load(ifs);
	boost::shared_ptr<Toki::Srx::Segmenter> segm(new Toki::Srx::NaiveIcuSegmenter);
	segm->load_rules(d.get_all_rules());

	BOOST_MESSAGE("Running " << (15 - 4) * 40 << " variable_window srx tests");

	UnicodeString us = UnicodeString::fromUTF8(t);
	for (int m = 4; m < 15; ++m) {
		for(int w = 40; w > 0; --w) {
			boost::shared_ptr<Toki::UnicodeIcuStringWrapper> isw;
			isw.reset(new Toki::UnicodeIcuStringWrapper(us));
			Toki::Srx::SourceWrapper srx(isw, segm, w, m);
			std::vector<int> breaks;
			int i = 0;
			while (srx.has_more_chars()) {
				if (srx.peek_begins_sentence()) {
					breaks.push_back(i);
				}
				++i;
				srx.get_next_char();
			}
			bool okay = true;
			int* a = &breaks[0];
			int* ae = a + breaks.size();
			int* b = tb;
			while (a < ae && b < tbe) {
				if (*a++ != *b++) {
					okay = false;
				}
			}
			if (a != ae || b != tbe) {
				okay = false;
			}
			BOOST_CHECK_MESSAGE(okay, "Mismatch for window " << w << " and margin " << m);
			BOOST_REQUIRE_EQUAL_COLLECTIONS(tb, tbe, breaks.begin(), breaks.end());
		}
	}

}



BOOST_AUTO_TEST_SUITE_END()
