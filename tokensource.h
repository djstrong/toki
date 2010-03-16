#ifndef TOKENSOURCE_H
#define TOKENSOURCE_H

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
};

#endif // TOKENSOURCE_H
