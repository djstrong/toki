#ifndef WHITESPACETOKENIZER_H
#define WHITESPACETOKENIZER_H

#include "unicodesource.h"
#include "tokenizer.h"
#include "token.h"

/**
 * A simple tokenizer that takes a UnicodeSource (i.e. continous text) and
 * outputs (via getNextToken) tokens split according to whitespace in the text.
 */
class WhitespaceTokenizer : public Tokenizer
{
public:
	/**
	 * Constructor
	 */
	WhitespaceTokenizer(const TokenizerConfig::Cfg& cfg = TokenizerConfig::Default());

	/**
	 * Constructor shorthand
	 * @see Tokenizer::Tokenizer
	 */
	WhitespaceTokenizer(UnicodeSource* us, const TokenizerConfig::Cfg& cfg = TokenizerConfig::Default());

	/// TokenSource override
	Token* getNextToken();

	/// Tokenizer override
	void reset();

protected:
	/// Tokenizer override
	void newInputSource();

private:
	/**
	 * Read characters from the input source until a non-white character is
	 * found, storing the amount/type of whitespace that was consumed.
	 */
	void eatWhitespace();

	/**
	 * Stored whitespace amount that preceeds the next token
	 */
	Token::WhitespaceAmount wa_;

	/**
	 * The type of tokens to return
	 */
	std::string token_type_;
};

#endif // WHITESPACETOKENIZER_H
