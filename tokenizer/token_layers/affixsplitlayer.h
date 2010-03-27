#ifndef AFFIXSPLITLAYER_H
#define AFFIXSPLITLAYER_H

#include "outputqueuelayer.h"

#include <unicode/utypes.h>

#include <set>

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

	AffixSplitLayer(TokenSource* input, const Properties& props);

protected:
	void prepareMoreTokens(Token* t);

private:
	bool isPrefixChar(UChar c);

	bool isPostfixChar(UChar c);

	std::set<UChar> prefix_chars_;

	std::set<UChar> postfix_chars_;

	std::string prefix_type_;

	std::string postfix_type_;
};

void foo();
#endif // AFFIXSPLITLAYER_H
