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

#ifndef LIBTOKI_PATHSEARCH_H
#define LIBTOKI_PATHSEARCH_H

#include <libtoki/util/confignode.h>

#include <unicode/unistr.h>

#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace Toki {

	class PathSearcher
	{
	public:
		/**
		 * Create a new PathSearcher with a separator and no paths.
		 * Note: the separator MUST be a single character.
		 */
		PathSearcher(const std::string& separator);

		/// Destructor
		virtual ~PathSearcher();

		/// Search path vector accesor
		const std::vector<std::string>& get_search_path() const;

		/// Search path string representation accesor
		std::string get_search_path_string() const;

		/// Seacrh path setter, vector of already-split paths
		void set_search_path(const std::vector<std::string> &paths);

		/// Search path setter, string with the paths separated by the separator
		void set_search_path(const std::string &);

		/// Separator accesor
		const std::string& get_path_separator() const;

		/**
		 * Look for a filename under the search path and return a path to a file
		 * that exists, or an empty string in case of failure
		 */
		std::string find_file(const std::string& filename);

		/**
		 * Convenience template wrapper around find_file to throw an exception
		 * when the file is not found.
		 *
		 * The passed exception class' constructor should take three parameters:
		 * the filename, the current search path string and the circumstance
		 * string (where).
		 */
		template<typename E>
		std::string find_file_throw(const std::string& filename,
				const std::string& where);

		/**
		 * Open a file stream for a file in the library search path
		 */
		bool open_stream(const std::string& filename, std::ifstream& ifs);

		/**
		 * Convenience template wrapper around open_stream to throw an exception
		 * when the file is not found.
		 *
		 * The passed exception class' constructor should take three parameters:
		 * the filename, the current search path string and the circumstance
		 * string (where).
		 */
		template<typename E>
		void open_stream_throw(const std::string& filename, std::ifstream& ifs,
				const std::string& where);

	private:
		/// The search paths
		std::vector<std::string> paths_;

		/// The path separator
		std::string separator_;
	};

	/**
	 * Convenience class to set the library config path and have it automatically
	 * reset to the original value upon destruction
	 */
	class ConfigPathSetter
	{
	public:
		/// Constructor
		ConfigPathSetter(PathSearcher& ps, const std::string& new_path);

		/// Destructor
		~ConfigPathSetter();
	private:
		/// The affected PathSearcher
		PathSearcher& ps_;

		/// Stored old path
		std::vector<std::string> old_path_;
	};

	/* Implementation */
	template<typename E>
	inline std::string PathSearcher::find_file_throw(const std::string& filename,
			const std::string& where)
	{
		std::string fn = find_file(filename);
		if (fn.empty()) {
			throw E(filename, get_search_path_string(), where);
		}
		return fn;
	}

	template<typename E>
	inline void PathSearcher::open_stream_throw(const std::string& filename,
			std::ifstream& ifs, const std::string& where)
	{
		if (!open_stream(filename, ifs)) {
			throw E(filename, get_search_path_string(), where);
		}
	}

} /* end ns Toki */

#endif // LIBTOKI_SETTINGS_H
