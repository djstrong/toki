#ifndef BASICSPLITLAYER_H
#define BASICSPLITLAYER_H

#include "outputqueuelayer.h"
#include <set>
#include <unicode/utypes.h>

/**
 * A layer to split tokens containing one of the listed characters. Extracted
 * characters are made into separate tokens with a given type, remaining bits
 * of the orth are made tokens with the original token's type.
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

	/// TokenLayer override
	virtual std::string info() const;
protected:
	/// OutputQueueTokenLayer override
	void prepareMoreTokens(Token* t);

private:
	/// test function for the split chars
	bool isSplitChar(UChar c);

	/// the split characters
	std::set<UChar> split_chars_;

	/// type of the extracted tokens
	std::string sep_type_;
};

#endif // BASICSPLITLAYER_H
