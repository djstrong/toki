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
	TokenizerConfig::Cfg* base_config;

	std::vector<fs::path> configs;

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

	TokenizerConfig::Cfg cfg;
	if (c.base_config != NULL) {
		cfg = *(c.base_config);
	}

	BOOST_FOREACH (const fs::path& p, c.configs) {
		TokenizerConfig::Cfg additional = TokenizerConfig::fromFile(p.string());
		TokenizerConfig::merge(cfg, additional);
	}

	LayerTokenizer tok(ifs_in, cfg);
	std::stringstream ss_expected;
	ss_expected << ifs_out.rdbuf();
	std::string actual = tok.debug_formatted();
	BOOST_CHECK_EQUAL (actual, ss_expected.str());

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
		//check fir name, load special config if possible, else default
		*cfg = TokenizerConfig::Default();
	}
	global_configs.push_back(boost::shared_ptr<TokenizerConfig::Cfg>(cfg));
	int count = 0;
	BOOST_FOREACH(const std::string& s, tests_out) {
		compare_item c;
		if (tests_in.find(s) == tests_in.end()) {
			if (tests_in.find("main") == tests_in.end()) {
				BOOST_TEST_MESSAGE("missing .in file : " << s);
				continue;
			} else {
				c.in_file = dir / "main.in";
			}
		} else {
			c.in_file = dir / (s + ".in");
		}
		c.out_file = dir / (s + ".out");
		c.base_config = cfg;
		if (configs.find(s) != configs.end()) {
			c.configs.push_back(dir / (s + ".ini"));
		}
		global_compares.push_back(c);
		++count;
	}
	BOOST_TEST_MESSAGE("Found " << count << " valid compare test case"
		<< (count > 1 ? "s" : "")
		<< " in " << dir);
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

