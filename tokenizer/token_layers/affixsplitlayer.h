#ifndef AFFIXSPLITLAYER_H
#define AFFIXSPLITLAYER_H

#include "outputqueuelayer.h"

#include <set>

/**
 * Layer to recognize and split prefix and posftix characters in tokens.
 * All prefix characters are extracted as separate tokens, then the unrecognized
 * part is output as the body token (with the type unmodified), and then the
 * postfix characters are output.
 */
class AffixSplitLayer : public OutputQueueLayer
{
public:
	/**
	 * Constructor.
	 *
	 * Keys recognized in the configuration:
	 * - prefix_chars  - List of prefix characters, treated as UTF-8 and
	 *                   unescaped. Defaults to empty.
	 * - postfix_chars - List of postfix characters, treated as UTF-8 and
	 *                   unescaped. Defaults to empty.
	 * - prefix_token_type  - Token type to set in the extracted prefixes.
	 *                        Defaults to "pre".
	 * - postfix_token_type - Token type to set in the extracted postfixes.
	 *                        Defaults to "post".
	 */

	AffixSplitLayer(TokenSource* input, const Config::Node& props);

	/// TokenLayer override
	virtual std::string info() const;

	/// TokenLayer override
	std::string long_info() const;

protected:
	/// OutputQueueLayer override
	void prepareMoreTokens(Token* t);

private:
	/// test function for prefix characters
	bool isPrefixChar(UChar c);

	/// test function for postfix characters
	bool isPostfixChar(UChar c);

	/// prefix characters
	std::set<UChar> prefix_chars_;

	/// postfix characters
	std::set<UChar> postfix_chars_;

	/// type of the extracted prefix tokens
	std::string prefix_type_;

	/// type of the extracted postfix tokens
	std::string postfix_type_;
};

#endif // AFFIXSPLITLAYER_H
