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

#ifndef LIBTOKI_EXCEPTION_H
#define LIBTOKI_EXCEPTION_H

#include <stdexcept>

namespace Toki {

	/**
	 * Base class for all tokenizer errors. Derives from
	 * @c std::runtime_error. Call member function @c what to get a
	 * human-readable message associated with the error.
	 */
	class TokenizerLibError : public std::runtime_error
	{
	public:
		/**
		 * Instantiate a TokenizerLibError instance with the given message.
		 * @param what The message to associate with this error.
		 */
		TokenizerLibError(const std::string &what);

		~TokenizerLibError() throw();

		virtual std::string info() const;
	};


	/**
	 * Class to signify "can't happen" errors
	 */
	class TokenizerImpossibleError : public TokenizerLibError
	{
	public:
		TokenizerImpossibleError(const std::string &what)
		 : TokenizerLibError(what)
		{
		}

		~TokenizerImpossibleError() throw()
		{
		}
	};

	class FileNotFound : public TokenizerLibError
	{
	public:
		FileNotFound(const std::string& filename, const std::string& paths,
				const std::string& where);

		~FileNotFound() throw();

		std::string info() const;

		std::string filename, paths, where;
	};

} /* end ns Toki */

#endif // LIBTOKI_EXCEPTION_H
