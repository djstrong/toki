#include "srx/util.h"

#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

BOOST_AUTO_TEST_SUITE( srx )

BOOST_AUTO_TEST_CASE( unquote )
{
	std::string s1 = "asdlkh\\asjkd\\.asd+{}\\alh\\\\asd21\\a";
	BOOST_CHECK_EQUAL( s1, Toki::Srx::Util::unquote_regex(s1) );
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

BOOST_AUTO_TEST_SUITE_END()
