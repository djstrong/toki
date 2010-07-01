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

#include <libtoki/token.h>
#include <libtoki/tokensource.h>

#include <ostream>
#include <sstream>

namespace Toki {

	TokenSource::TokenSource()
	{
	}

	TokenSource::~TokenSource()
	{
	}

	void TokenSource::tokenize(boost::function<void(Token *)> sink)
	{
		while (Token* t = get_next_token()) {
			sink(t);
		}
	}

} /* end namespace Toki */
