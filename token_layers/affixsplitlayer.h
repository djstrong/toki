#ifndef AFFIXSPLITLAYER_H
#define AFFIXSPLITLAYER_H

#include "outputqueuelayer.h"

#include <unicode/utypes.h>

#include <set>

class AffixSplitLayer : public OutputQueueLayer
{
public:
	AffixSplitLayer(TokenSource* input, const Properties& props);

	static bool registered;

protected:
	void prepareMoreTokens();

private:
	bool isPrefixChar(UChar c);

	bool isPostfixChar(UChar c);

	std::set<UChar> prefix_chars_;

	std::set<UChar> postfix_chars_;

	std::string prefix_type_;

	std::string postfix_type_;
};

#endif // AFFIXSPLITLAYER_H
