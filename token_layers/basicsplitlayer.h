#ifndef BASICSPLITLAYER_H
#define BASICSPLITLAYER_H

#include "outputqueuelayer.h"
#include <set>
#include <unicode/utypes.h>

class BasicSplitLayer : public OutputQueueLayer
{
public:
	BasicSplitLayer(TokenSource* input, const Properties& props);

	static bool registered;

protected:
	void prepareMoreTokens(Token* t);

private:
	bool isSplitChar(UChar c);

	std::set<UChar> split_chars_;

	std::string sep_type_;
};

#endif // BASICSPLITLAYER_H
