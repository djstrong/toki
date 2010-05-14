#ifndef LIBTOKI_REGEXMATCHSPLITLAYER_H
#define LIBTOKI_REGEXMATCHSPLITLAYER_H

#include "outputqueuelayer.h"
#include <unicode/regex.h>

namespace Toki {

/**
 * A layer to extract parts of a token that mach a specified regular expression.
 * Parts that match are extracted into separate tokens with the given type,
 * remaining parts retain the original token's type.
 */
class RegexMatchSplitLayer : public OutputQueueLayer
{
public:
	/**
	 * Constructor.
	 *
	 * Keys recognized in the configuration:
	 * - regexseparators - The regular expression to use.
	 * - separator_token_type - Type to set in the extracted tokens. Defaults
	 *                          to "sep".
	 */
	RegexMatchSplitLayer(TokenSource* input, const Config::Node& props);

	/// TokenLayer override
	virtual std::string info() const;

	/// TokenLayer override
	std::string long_info() const;

	/// getter for the separator (extracted token) type
	const std::string& separator_type() const {
		return sep_type_;
	}
protected:
	/// OutputQueueLayer override
	void prepare_more_tokens(Token *t);

private:
	/// the regex
	RegexMatcher* regex_;

	/// token type for extracted token parts
	std::string sep_type_;
};

} /* end ns Toki */

#endif // LIBTOKI_REGEXMATCHSPLITLAYER_H
