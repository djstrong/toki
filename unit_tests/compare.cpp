#include "layertokenizer.h"
#include "compare.h"

#include <fstream>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <map>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

namespace fs = boost::filesystem;


static const char subdir_name[] = "test_compare";

//BOOST_AUTO_TEST_SUITE( test_compare )
struct compare_item
{
	TokenizerConfig::Cfg* config;

	fs::path in_file;

	fs::path out_file;
};

static std::vector< boost::shared_ptr<TokenizerConfig::Cfg> > global_configs;

static std::vector< compare_item > global_compares;

void test_one_item(const compare_item& c)
{
	fs::path file_in = c.in_file;
	fs::path file_out = c.out_file;
	BOOST_REQUIRE_MESSAGE(fs::exists(file_in), "Input file " << file_in << " not found!");
	BOOST_REQUIRE_MESSAGE(fs::exists(file_out), "Expected output file " << file_out << " not found!");
	fs::ifstream ifs_in(file_in);
	fs::ifstream ifs_out(file_out);
	LayerTokenizer tok(ifs_in, *c.config);
	std::stringstream ss;
	tok.debug_orths_newline(ss);
	std::stringstream ss_expected;
	ss_expected << ifs_out.rdbuf();
	BOOST_CHECK_EQUAL( ss.str(), ss_expected.str() );
}

void subdir_exists()
{
	BOOST_REQUIRE_MESSAGE(fs::exists(subdir_name),
		subdir_name << " directory must exist");
	BOOST_REQUIRE_MESSAGE(fs::is_directory(subdir_name),
		subdir_name << " must be a directory");
}

void init_subdir(fs::path dir)
{
	fs::directory_iterator end_itr; // default construction yields past-the-end

	std::set<std::string> tests_in;
	std::set<std::string> tests_out;
	std::set<std::string> configs;
	std::set<fs::path> subdirs;
	for (fs::directory_iterator itr(dir); itr != end_itr; ++itr) {
		if (fs::is_directory(itr->status())) {
			subdirs.insert(itr->path());
		} else {
			if (itr->path().extension() == ".in") {
				tests_in.insert(itr->path().stem());
			} else if (itr->path().extension() == ".out") {
				tests_out.insert(itr->path().stem());
			} else if (itr->path().extension() == ".ini") {
				configs.insert(itr->path().stem());
			}
		}
	}
	std::set<std::string>::iterator i = configs.find("main");
	TokenizerConfig::Cfg* cfg = new TokenizerConfig::Cfg();
	if (i != configs.end()) {
		std::string p = (dir / "main.ini").string();
		*cfg = TokenizerConfig::fromFile(p);
	} else {
		*cfg = TokenizerConfig::Default();
	}
	global_configs.push_back(boost::shared_ptr<TokenizerConfig::Cfg>(cfg));
	BOOST_FOREACH(const std::string& s, tests_out) {
		compare_item cmp;
		if (tests_in.find(s) == tests_in.end()) {
			if (tests_in.find("main") == tests_in.end()) {
				BOOST_TEST_MESSAGE("massing .in file : " << s);
				continue;
			} else {
				cmp.in_file = dir / "main.in";
			}
		} else {
			cmp.in_file = dir / (s + ".in");
		}
		cmp.out_file = dir / (s + ".out");
		if (configs.find(s) == configs.end()) {
			cmp.config = cfg;
		} else {
			cmp.config = new TokenizerConfig::Cfg();
			std::string p = (dir / (s + ".ini")).string();
			*cmp.config = TokenizerConfig::fromFile(p);
			global_configs.push_back(boost::shared_ptr<TokenizerConfig::Cfg>(cmp.config));
		}
		global_compares.push_back(cmp);
	}
	BOOST_FOREACH(const fs::path& s, subdirs) {
		init_subdir(s);
	}
}


void init_compare_suite(boost::unit_test::test_suite *ts)
{
	ts->add(BOOST_TEST_CASE(&subdir_exists));
	if (!fs::exists(subdir_name)) return;
	init_subdir(subdir_name);
	ts->add(BOOST_PARAM_TEST_CASE(test_one_item, &global_compares[0],
		&global_compares[0] + global_compares.size()));
}



//BOOST_AUTO_TEST_SUITE_END()

