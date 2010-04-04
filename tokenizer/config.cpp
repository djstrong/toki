#include "config.h"

#include "parser/loose_ini_paser.h"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

#include "exception.h"

namespace Config {

Node fromFile(const std::string &filename)
{
	Node p;
	try {
		loose_ini_parser::read_loose_ini(filename, p);
	} catch (boost::property_tree::file_parser_error& e) {
		throw TokenizerLibError(e.what());
	}

	return p;
}

Node fromStream(std::istream &is)
{
	Node p;
	try {
		boost::property_tree::ini_parser::read_ini(is, p);
	} catch (boost::property_tree::file_parser_error& e) {
		throw TokenizerLibError(e.what());
	}
	return p;
}

Node& merge_into(Node& accu, const Node& other)
{
	accu.data() = other.data();
	using boost::property_tree::ptree;
	BOOST_FOREACH (const ptree::value_type& in_other, other) {
		boost::optional< ptree& > in_one;
		if ((in_one = accu.get_child_optional(in_other.first))) {
			merge_into(*in_one, in_other.second);
		} else {
			accu.push_back(in_other);
		}
	}
	return accu;
}

Node merge_copy(const Node &one, const Node &other)
{
	Node accu(one);
	merge_into(accu, other);
	return accu;
}

void write(const Node &c, const std::string &filename)
{
	int errors = 0;
	try {
		boost::property_tree::ini_parser::write_ini(filename + ".ini", c);
	} catch (boost::property_tree::file_parser_error& e) {
		errors++;
	}
	try {
		boost::property_tree::xml_parser::write_xml(filename + ".xml", c);
	} catch (boost::property_tree::file_parser_error& e) {
		errors++;
	}
	try {
		boost::property_tree::json_parser::write_json(filename + ".json", c);
	} catch (boost::property_tree::file_parser_error& e) {
		errors++;
	}
	if (errors > 0) {
		std::cerr << "Config write failed!\n";
	}
}

const Node& Default()
{
	bool initialized = false;
	static Node cfg;
	if (!initialized) {
		try {
			cfg = get_library_config("config.ini");
		} catch (TokenizerLibError& e) {
			throw TokenizerLibError(std::string("Default config error! ") + e.what());
		}
		initialized = true;
	}
	return cfg;
}

namespace {
	static std::vector<std::string> library_config_path;

	std::string get_library_config_path_string()
	{
		return boost::algorithm::join(library_config_path, std::string(";"));
	}
} // end anon namespace

Node get_library_config(const std::string &id)
{
	namespace fs = boost::filesystem;
	fs::path i(id);
	BOOST_FOREACH (const std::string& s, library_config_path) {
		fs::path p(s);
		fs::path pi = s / i;
		if (fs::exists(pi) && fs::is_regular(pi)) {
			return fromFile(pi.string());
		}
	}
	std::stringstream ss;
	ss << "Library config ``" << id << "'' not found in search path: ";
	ss << get_library_config_path_string();
	throw TokenizerLibError(ss.str());
}

std::vector<std::string> get_library_config_path()
{
	return library_config_path;
}

void set_library_config_path(const std::vector<std::string> &vec)
{
	library_config_path = vec;
}

void set_library_config_path(const std::string &s)
{
	std::vector<std::string> v;
	boost::algorithm::split(v, s, std::bind1st(std::equal_to<char>(), ';'));
	set_library_config_path(v);
}

namespace {
	bool init_lcp()
	{
#ifdef LIBTOKENIZER_CONFIG_PATH
		set_library_config_path(LIBTOKENIZER_CONFIG_PATH);
#else
		set_library_config_path("..");
#endif
		return !library_config_path.empty();
	}

	static bool lcp_init = init_lcp();
} //end anon namespace

} //end namespace Config

