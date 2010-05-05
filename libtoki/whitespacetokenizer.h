#ifndef LIBTOKI_WHITESPACETOKENIZER_H
#define LIBTOKI_WHITESPACETOKENIZER_H

#include "unicodesource.h"
#include "tokenizer.h"
#include "token.h"

namespace Toki {

	namespace Srx {
		class SourceWrapper;
	}

	/**
	 * A simple tokenizer that takes a UnicodeSource (i.e. continous text) and
	 * outputs (via get_next_token) tokens split according to whitespace in the text.
	 */
	class WhitespaceTokenizer : public Tokenizer
	{
	public:
		/**
		 * Constructor
		 *
		 * Keys recognized in the configuration:
		 * - token_type - Token type to set in created tokens, default_configs to "t".
		 * - initial_whitespace - Whitespace to set in the first extracted
		 *                        token, can be a descriptor or a string with
		 *                        the actual whitespace, use \u0020 for a space.
		 */
		WhitespaceTokenizer(const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand
		 * @see Tokenizer::Tokenizer
		 */
		WhitespaceTokenizer(UnicodeSource* us, const Config::Node& cfg = Config::default_config());

		/// TokenSource override
		Token* get_next_token();

		/// Tokenizer override
		void reset();

	protected:
		/// Tokenizer override
		void new_input_source();

		/// process configuration helper for the constructors
		void process_config(const Config::Node& cfg);

	private:
		/**
		 * Read characters from the input source until a non-white character is
		 * found, storing the amount/type of whitespace that was consumed.
		 */
		void eat_whitespace();

		/**
		 * Stored whitespace amount that preceeds the next token
		 */
		Token::WhitespaceAmount wa_;

		/**
		 * The type of tokens to return
		 */
		std::string token_type_;

		/**
		 * Initial whitespace for the first token
		 */
		Token::WhitespaceAmount initial_wa_;

		/**
		 * Token begins_sentence flag
		 */
		bool begins_sentence_;

		boost::shared_ptr<Srx::SourceWrapper> srx_;
	};

} //end namespace Toki

#endif // LIBTOKI_WHITESPACETOKENIZER_H
