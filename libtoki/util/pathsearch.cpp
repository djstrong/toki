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

#include <libtoki/util/pathsearch.h>

#include <libtoki/exception.h>
#include <libtoki/util/foreach.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>

namespace Toki {

	PathSearcher::PathSearcher(const std::string& separator)
		: paths_(), separator_(separator)
	{
		if (separator.empty()) {
			std::cerr << "No path separator! Defaulting to :\n";
		} else if (separator.size() > 1) {
			std::cerr << "Separator size > 1, truncating: '" << separator << "'\n";
			separator_ = separator_[0];
		}
	}

	PathSearcher::~PathSearcher()
	{
	}

	const std::vector<std::string>& PathSearcher::get_search_path() const
	{
		return paths_;
	}

	std::string PathSearcher::get_search_path_string() const
	{
		return boost::algorithm::join(paths_, separator_);
	}

	void PathSearcher::set_search_path(const std::vector<std::string> &paths)
	{
		paths_ = paths;
	}

	void PathSearcher::set_search_path(const std::string &paths)
	{
		paths_.clear();
		boost::algorithm::split(paths_, paths,
			std::bind1st(std::equal_to<char>(), separator_[0]));
	}

	const std::string& PathSearcher::get_path_separator() const
	{
		return separator_;
	}

	std::string PathSearcher::find_file(const std::string& filename)
	{
		boost::filesystem::path i(filename);
		foreach (const std::string& s, paths_) {
			boost::filesystem::path pi = s / i;
			if (boost::filesystem::exists(pi) && boost::filesystem::is_regular(pi)) {
				return pi.string();
			}
		}
		return "";
	}

	bool PathSearcher::open_stream(const std::string& filename, std::ifstream& ifs)
	{
		std::string f = find_file(filename);
		if (!f.empty()) {
			ifs.open(f.c_str());
			return true;
		}
		return false;
	}

	ConfigPathSetter::ConfigPathSetter(PathSearcher& ps, const std::string &new_path)
		: ps_(ps), old_path_(ps.get_search_path())
	{
		ps_.set_search_path(new_path);
	}

	ConfigPathSetter::~ConfigPathSetter()
	{
		ps_.set_search_path(old_path_);
	}

} /* end namespace Toki */
