#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iosfwd>
class Token;
class TokenSource;

#include "tokensource.h"

namespace Debug {

	void sink_to_stream(boost::function<std::string (const Token&)> func, std::ostream& os, Token* t);

	std::string tokenize(TokenSource& tok, boost::function<std::string (const Token&)> func);

	std::string token_format(const std::string& format, const Token& t);

	std::string token_debug(const Token& t);

	std::string tokenize_orths_newline(TokenSource& ts);

	void tokenize_orths_newline(TokenSource& ts, std::ostream& os);

	/**
	 * Return a string with all tokens processed and printed according to the
	 * given format string. The following replacements will be done:
	 * - $orth   -> the token's orth
	 * - $type   -> the token's type
	 * - $ws     -> the preceeding whitespace amount string representation
	 *              e.g. "none". @see Token::WhitespaceAmount
	 * - $ws_id  -> the preceeding whitespace numeric code, 0 for no whtespace
	 * - $ws_any -> 0 if there was any whitespace preceeding the token, else 1
	 */
	std::string tokenize_formatted(TokenSource& tok, const std::string& format);

	void tokenize_formatted(TokenSource& tok, const std::string& format, std::ostream& os);

} //end namespace Debug

#endif // DEBUG_H
