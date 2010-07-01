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

#ifndef LIBTOKI_TOKENSOURCE_H
#define LIBTOKI_TOKENSOURCE_H

#include <boost/function.hpp>

#include <iosfwd>

namespace Toki {

	class Token;

	/**
	 * A simple interface for classes that can be used as token sources, for example
	 * token processing layers.
	 */
	class TokenSource
	{
	public:
		/// Constructor
		TokenSource();

		/// Destructor
		virtual ~TokenSource();

		/**
		 * Get the next token, or NULL if there are no more tokens.
		 * Caller takes ownership of the token.
		 */
		virtual Token* get_next_token() = 0;

		/**
		 * Tokenization helper. Tokenizes the entire input, calling the sink
		 * functor or each token. The sink takes ownership of the token.
		 */
		void tokenize(boost::function<void (Token*)> sink);
	};

} /* end ns Toki */


#endif // LIBTOKI_TOKENSOURCE_H
