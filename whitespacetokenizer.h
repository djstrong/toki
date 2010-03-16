#ifndef WHITESPACETOKENIZER_H
#define WHITESPACETOKENIZER_H

#include "unicodesource.h"
#include "tokensource.h"
#include "token.h"

/**
 * A simple tokenizer that takes a UnicodeSource (i.e. continous text) and
 * outputs (via getNextToken) tokens split according to whitespace in the text.
 */
class WhitespaceTokenizer : public TokenSource
{
public:
	/**
	 * Constructor.
	 * @param us The UnicodeSource with the text to tokenize
	 */
	WhitespaceTokenizer(UnicodeSource& us);

	/**
	 * TokenSource override
	 */
	Token* getNextToken();

private:
	/**
	 * Read characters from the input source until a non-white character is
	 * found, storing the amount/type of whitespace that was consumed.
	 */
	void eatWhitespace();

	/**
	 * The source of the text
	 */
	UnicodeSource& us_;

	/**
	 * Stored whitespace amount that preceeds the next token
	 */
	Token::WhitespaceAmount wa_;
};

#endif // WHITESPACETOKENIZER_H
