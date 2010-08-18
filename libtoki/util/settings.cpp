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

#ifdef HAVE_CONFIG_D_H
#include <libtoki/config_d.h>
#endif

#include <libtoki/exception.h>
#include <libtoki/util/foreach.h>
#include <libtoki/parser/loose_ini_paser.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

namespace Toki { namespace Config {

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

		static std::string separator_string = LIBTOKI_PATH_SEPARATOR;
	} // end anon namespace

	std::string get_library_config_path_string()
	{
		return boost::algorithm::join(library_config_path, separator_string);
	}

	const std::string& get_path_separator()
	{
		return separator_string;
	}

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
			std::cerr << "Loading tokenizer configuration from " << fn << "\n";
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
		boost::algorithm::split(v, s, std::bind1st(std::equal_to<char>(), LIBTOKI_PATH_SEPARATOR[0]));
		set_library_config_path(v);
	}

	namespace {
		bool init_lcp()
		{
	#ifdef LIBTOKI_DATA_DIR
			set_library_config_path(LIBTOKI_DATA_DIR);
	#else
			set_library_config_path(".");
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
