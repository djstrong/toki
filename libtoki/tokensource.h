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
#include <boost/range.hpp>

#include <iosfwd>
#include <vector>

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

	/**
	 * Generic TokenSource wrapper for containers of tagger Token pointers,
	 * e.g. a std::vector<Token*> or a boost::range of Token* iterators.
	 *
	 * The container should not be modified as long as it is being accesed
	 * by a RangeSource wrapper.
	 */
	template<typename T>
	class RangeSource : public TokenSource
	{
	public:
		typedef typename T::const_iterator const_iterator;

		RangeSource(const T& range)
			: end_(range.end()), ptr_(range.begin())
		{
		}

		Token* get_next_token()
		{
			if (ptr_ != end_) {
				return *ptr_++;
			} else {
				return NULL;
			}
		}

	private:
		const_iterator end_;

		const_iterator ptr_;
	};

	template<class T>
	RangeSource<T>* make_range_source(const T& range)
	{
		return new RangeSource<T>(range);
	}

	template<class T>
	RangeSource<boost::iterator_range<T> >* make_range_source(const T& b, const T& e)
	{
		boost::iterator_range<T> range(b, e);
		return new RangeSource< boost::iterator_range<T> >(range);
	}
} /* end ns Toki */


#endif // LIBTOKI_TOKENSOURCE_H
