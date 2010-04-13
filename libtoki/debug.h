#ifndef LIBTOKI_DEBUG_H
#define LIBTOKI_DEBUG_H

#include <string>
#include <iosfwd>
class Token;
class TokenSource;

#include "tokensource.h"

namespace Toki { namespace Debug {

	/**
	 * Helper function to pass a token through a given function and feed the
	 * resulting std::strings into an ostream
	 */
	void sink_to_stream(boost::function<std::string (const Token&)> func, std::ostream& os, Token* t);

	/**
	 * Tokenize the tokens from the TokenSource by passing all tokens through
	 * the given functon and concatenating the output std::strings.
	 */
	std::string tokenize(TokenSource& tok, boost::function<std::string (const Token&)> func);

	/**
	 * Formatted token debug output. The following replacements will be done:
	 * - $orth   -> the token's orth
	 * - $type   -> the token's type
	 * - $ws     -> the preceeding whitespace amount string representation
	 *              e.g. "none". @see Token::WhitespaceAmount
	 * - $ws_id  -> the preceeding whitespace numeric code, 0 for no whitespace
	 * - $ws_any -> 0 if there was any whitespace preceeding the token, else 1
	 *
	 * The format string will usually be unescaped before getting here, so
	 * e.g. backslash-n is usually a valid way of putting a newline into the
	 * debug output.
	 */
	std::string token_format(const std::string& format, const Token& t);

	/**
	 * "Standard" token debug output
	 */
	std::string token_debug(const Token& t);

	/**
	 * "Standard" debug tokenization -- orths with newline, equivalent to a
	 * $orth\n format.
	 */
	std::string tokenize_orths_newline(TokenSource& ts);

	/**
	 * "Standard" debug tokenization -- orths with newline, equivalent to a
	 * $orth\n format.
	 */
	void tokenize_orths_newline(TokenSource& ts, std::ostream& os);

	/**
	 * Return a string with all tokens processed and printed according to the
	 * given format string, @see token_format for format options.
	 */
	std::string tokenize_formatted(TokenSource& tok, const std::string& format);

	/**
	 * Output into the stream all tokens processed and printed according to the
	 * given format string, @see token_format for format options.
	 */
	void tokenize_formatted(TokenSource& tok, const std::string& format, std::ostream& os);

} /*end ns Debug */ } /* end ns Toki */

#endif // LIBTOKI_DEBUG_H
