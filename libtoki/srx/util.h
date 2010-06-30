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

#ifndef LIBTOKI_SRX_UTIL_H
#define LIBTOKI_SRX_UTIL_H

#include <string>

namespace Toki { namespace Srx {

	namespace Util {

		std::string unquote_regex(const std::string& re);

		std::string prepare_regex_for_lookbehind(const std::string& re, int max_lookbehind);

	} /* end ns Util */

} /* end ns Srx */ } /* end ns Toki */


#endif // UTIL_H
