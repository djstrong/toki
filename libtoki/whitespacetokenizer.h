#ifndef LIBTOKI_WHITESPACETOKENIZER_H
#define LIBTOKI_WHITESPACETOKENIZER_H

#include "unicodesource.h"
#include "tokenizer.h"
#include "token.h"

namespace Toki {

	/**
	 * A simple tokenizer that takes a UnicodeSource (i.e. continous text) and
	 * outputs (via getNextToken) tokens split according to whitespace in the text.
	 */
	class WhitespaceTokenizer : public Tokenizer
	{
	public:
		/**
		 * Constructor
		 *
		 * Keys recognized in the configuration:
		 * - token_type - Token type to set in created tokens, defaults to "t".
		 *
		 */
		WhitespaceTokenizer(const Config::Node& cfg = Config::Default());

		/**
		 * Constructor shorthand
		 * @see Tokenizer::Tokenizer
		 */
		WhitespaceTokenizer(UnicodeSource* us, const Config::Node& cfg = Config::Default());

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

} //end namespace Toki

#endif // LIBTOKI_WHITESPACETOKENIZER_H
