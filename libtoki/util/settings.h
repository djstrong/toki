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

#ifndef LIBTOKI_SETTINGS_H
#define LIBTOKI_SETTINGS_H

#include <libtoki/util/confignode.h>

#include <unicode/unistr.h>

#include <boost/property_tree/ptree.hpp>

#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace Toki { namespace Config {

	/**
	 * The default_config configuration node
	 */
	const Node& default_config();

	/**
	 * Look for a filename under the search path and return a path to a file
	 * that exists, or an empty string in case of failure
	 */
	std::string find_file_in_search_path(const std::string& filename);

	/**
	 * Open a file stream for a file in the library search path
	 */
	bool open_file_from_search_path(const std::string& filename, std::ifstream& ifs);

	/**
	 * Get a default_config config by name
	 */
	Node get_library_config(const std::string& id);

	std::vector<std::string> get_library_config_path();

	void set_library_config_path(const std::vector<std::string> &);

	void set_library_config_path(const std::string &);

	/**
	 * Convenience class to set the library config path and have it automatically
	 * reset to the original value upon destruction
	 */
	class LibraryConfigPathSetter
	{
	public:
		/// Constructor
		LibraryConfigPathSetter(const std::string& new_path);

		/// Destructor
		~LibraryConfigPathSetter();
	private:
		/// Stored old path
		std::vector<std::string> old_path_;
	};

	/**
	 * Get the default error stream used by the library to log errors
	 */
	std::ostream* get_default_error_stream();

	/**
	 * Set the default error stream used by the library to log errors.
	 * NULL disables error logging.
	 */
	void set_default_error_stream(std::ostream* os);

} /* end ns Config */ } /* end ns Toki */

#endif // LIBTOKI_SETTINGS_H
