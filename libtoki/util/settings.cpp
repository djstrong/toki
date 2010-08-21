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

namespace Toki {

	TokiPathSearcher::TokiPathSearcher()
		: PathSearcher(LIBTOKI_PATH_SEPARATOR)
	{
		set_search_path(LIBTOKI_DATA_DIR);
	}

	const Config::Node& default_config()
	{
		bool initialized = false;
		static Config::Node cfg;
		if (!initialized) {
			try {
				cfg = get_named_config("config");
			} catch (TokenizerLibError& e) {
				throw TokenizerLibError(std::string("default_config config error! ") + e.what());
			}
			initialized = true;
		}
		return cfg;
	}

	Config::Node get_named_config(const std::string &id)
	{
		std::string fn = Path::Instance().find_file(id + ".ini");
		if (!fn.empty()) {
			std::cerr << "Loading tokenizer configuration from " << fn << "\n";
			return Config::from_file(fn);
		} else {
			std::stringstream ss;
			ss << "Library config ``" << id << "'' not found in search path: ";
			ss << Path::Instance().get_search_path_string();
			throw TokenizerLibError(ss.str());
		}
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

} /* end namespace Toki */
