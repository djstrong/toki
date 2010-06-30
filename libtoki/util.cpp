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

#include <libtoki/util.h>

namespace Toki { namespace Util {

	std::string unescape_utf8(const std::string& str)
	{
		std::string out;
		UnicodeString u = UnicodeString::fromUTF8(str).unescape();
		u.toUTF8String(out);
		return out;
	}

	std::string to_utf8(const UnicodeString &ustr)
	{
		std::string s;
		ustr.toUTF8String(s);
		return s;
	}

} /* end namespace Util */ } /* end namespace Toki */
