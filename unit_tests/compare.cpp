#include "layertokenizer.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace fs = boost::filesystem;

#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

static const char subdir_name[] = "test_compare";

//BOOST_AUTO_TEST_SUITE( test_compare )

typedef std::pair<const TokenizerConfig::Cfg*, std::string> compare_item;

static std::list<TokenizerConfig::Cfg> configs;

void test_one_item(const compare_item& c)
{
	std::string file_in = c.second + ".in";
	std::string file_out = c.second + ".out";
	BOOST_REQUIRE_MESSAGE(fs::exists(file_in), "Input file " << file_in << " not found!");
	BOOST_REQUIRE_MESSAGE(fs::exists(file_out), "Expected output file " << file_out << " not found!");
	std::ifstream ifs_in(file_in.c_str());
	std::ifstream ifs_out(file_out.c_str());
	LayerTokenizer tok(ifs_in, *c.first);
	std::stringstream ss;
	tok.debug_orths_newline(ss);
	std::stringstream ss_expected;
	ss_expected << ifs_out.rdbuf();
	BOOST_CHECK_EQUAL( ss.str(), ss_expected.str() );
}

BOOST_AUTO_TEST_CASE( subdir_exists )
{
	BOOST_REQUIRE( fs::exists(subdir_name) );
	BOOST_REQUIRE( fs::is_directory(subdir_name) );
}

bool prep_test_cases()
{
	if (!fs::exists( subdir_name)) return false;
	fs::directory_iterator end_itr; // default construction yields past-the-end
	std::vector<compare_item> tests;
	configs.push_back(TokenizerConfig::Default());
	TokenizerConfig::Cfg* def = &configs.back();
	for (fs::directory_iterator itr(subdir_name); itr != end_itr; ++itr) {
		if (is_directory(itr->status())) {
			//
		} else {
			if (boost::algorithm::ends_with(itr->leaf(), ".in")) {
				std::string path = itr->path().string();
				std::string base = path.substr(0, path.size() - 3);
				tests.push_back(std::make_pair(def, base));
			}
		}
	}
	boost::unit_test::framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(
		test_one_item, &tests[0], &tests[0] + tests.size()));

	return true;
}

boost::unit_test::test_suite* init_unit_test_suite(int argc, char* argv[])
{
	std::cerr << "!!!\n";
	prep_test_cases();
	return 0;
}

//BOOST_AUTO_TEST_SUITE_END()

