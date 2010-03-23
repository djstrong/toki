#ifndef TOKENSOURCE_H
#define TOKENSOURCE_H

class Token;
#include <iosfwd>

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
	 * Debug aid to tokenize everything and output the resulting orths into
	 * the stream, one per line.
	 */
	void debug_orths_newline(std::ostream& os);

	/**
	 * Debug aid to tokenize everything and return the resulting orths,
	 * one per line.
	 */
	std::string debug_orths_newline();

	/**
	 * Debug aid to tokenize everything and output the resulting tokens into,
	 * the stream using Token's debug print.
	 */
	void debug_tokenize(std::ostream& os);

	/**
	 * Debug aid to tokenize everything and return the resulting tokens,
	 * concatenated, using Token's debug print.
	 */
	std::string debug_tokenize();
};

#endif // TOKENSOURCE_H
