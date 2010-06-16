#include <libtoki/config.h>

#ifdef HAVE_CONFIG_D_H
#include <libtoki/config_d.h>
#endif

#include <libtoki/foreach.h>

#include <libtoki/parser/loose_ini_paser.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

#include <libtoki/exception.h>

namespace Toki { namespace Config {

	Node from_file(const std::string &filename)
	{
		Node p;
		try {
			loose_ini_parser::read_loose_ini(filename, p);
		} catch (boost::property_tree::file_parser_error& e) {
			throw TokenizerLibError(e.what());
		}

		return p;
	}

	Node from_stream(std::istream &is)
	{
		Node p;
		try {
			loose_ini_parser::read_loose_ini(is, p);
		} catch (boost::property_tree::file_parser_error& e) {
			throw TokenizerLibError(e.what());
		}
		return p;
	}

	Node& merge_into(Node& accu, const Node& other)
	{
		accu.data() = other.data();
		using boost::property_tree::ptree;
		foreach (const ptree::value_type& in_other, other) {
			boost::optional< ptree& > in_one;
			if ((in_one = accu.get_child_optional(in_other.first))) {
				if (in_other.second.get("_merge", "") == "override") {
					*in_one = in_other.second;
				} else {
					merge_into(*in_one, in_other.second);
				}
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

	const Node& default_config()
	{
		bool initialized = false;
		static Node cfg;
		if (!initialized) {
			try {
				cfg = get_library_config("config");
			} catch (TokenizerLibError& e) {
				throw TokenizerLibError(std::string("default_config config error! ") + e.what());
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

	std::string find_file_in_search_path(const std::string &filename)
	{
		namespace fs = boost::filesystem;
		fs::path i(filename);
		foreach (const std::string& s, library_config_path) {
			fs::path pi = s / i;
			if (fs::exists(pi) && fs::is_regular(pi)) {
				return pi.string();
			}
		}
		return "";
	}

	bool open_file_from_search_path(const std::string &filename, std::ifstream &ifs)
	{
		std::string f = find_file_in_search_path(filename);
		if (!f.empty()) {
			ifs.open(f.c_str());
			return true;
		}
		return false;
	}

	Node get_library_config(const std::string &id)
	{
		std::string fn = find_file_in_search_path(id + ".ini");
		if (!fn.empty()) {
			return from_file(fn);
		} else {
			std::stringstream ss;
			ss << "Library config ``" << id << "'' not found in search path: ";
			ss << get_library_config_path_string();
			throw TokenizerLibError(ss.str());
		}
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
	#ifdef LIBTOKI_DATA_DIR
			set_library_config_path(LIBTOKI_DATA_DIR);
	#else
			set_library_config_path("..");
	#endif
			return !library_config_path.empty();
		}

		static bool lcp_init = init_lcp();
	} //end anon namespace

	LibraryConfigPathSetter::LibraryConfigPathSetter(const std::string &new_path)
		: old_path_(get_library_config_path())
	{
		set_library_config_path(new_path);
	}

	LibraryConfigPathSetter::~LibraryConfigPathSetter()
	{
		set_library_config_path(old_path_);
	}

	namespace {
		std::ostream* default_error_stream_ = NULL;
		bool des_init_ = false;
	} // end namespace

	std::ostream* get_default_error_stream()
	{
		if (!des_init_) {
			set_default_error_stream(&std::cerr);
		}
		return default_error_stream_;
	}

	void set_default_error_stream(std::ostream *os)
	{
		des_init_ = true;
		default_error_stream_ = os;
	}

} /* end ns Config */ } /* end namespace Toki */
