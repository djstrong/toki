#ifndef TOKENSOURCE_H
#define TOKENSOURCE_H

#include <iosfwd>
#include <boost/function.hpp>

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
		virtual Token* getNextToken() = 0;

		/**
		 * Tokenization helper. Tokenizes the entire input, calling the sink
		 * functor or each token. The sink takes ownership of the token.
		 */
		void tokenize(boost::function<void (Token*)> sink);
	};

} /* end ns Toki */


#endif // TOKENSOURCE_H
