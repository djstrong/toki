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

#ifndef LIBTOKI_SRX_EXCEPTION_H
#define LIBTOKI_SRX_EXCEPTION_H

#include <libtoki/exception.h>

namespace Toki {
namespace Srx {

class Error : public ::Toki::Error
{
public:
	Error(const std::string& what)
		: ::Toki::Error("SRX error: " + what)
	{
	}

	~Error() throw()
	{
	}
};

} /* end ns Srx */ }
/* end ns Toki */

#endif // LIBTOKI_SRX_EXCEPTION_H
