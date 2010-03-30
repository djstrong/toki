#ifndef BASICSPLITLAYER_H
#define BASICSPLITLAYER_H

#include "outputqueuelayer.h"
#include <set>
#include <unicode/utypes.h>

/**
 * A layer to split tokens containing one of the listed characters so they are
 * always separate tokens.
 */
class BasicSplitLayer : public OutputQueueLayer
{
public:
	/**
	 * Constructor.
	 *
	 * Keys recognized in the configuration:
	 * - separators - List of characters treated as spearators, treated as UTF-8
	 *                and unescaped. Defaults to empty.
	 * - separator_token_type - Type to set in the separator tokens. Defaults
	 *                          to "sep".
	 */
	BasicSplitLayer(TokenSource* input, const Config::Node& props);

protected:
	/// OutputQueueTokenLayer override
	void prepareMoreTokens(Token* t);

private:
	bool isSplitChar(UChar c);

	std::set<UChar> split_chars_;

	std::string sep_type_;
};

#endif // BASICSPLITLAYER_H
