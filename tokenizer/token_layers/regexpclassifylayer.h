#ifndef REGEXPCLASSIFYLAYER_H
#define REGEXPCLASSIFYLAYER_H

#include "tokenlayer.h"
#include <unicode/regex.h>

class RegexpClassifyLayer : public TokenLayer
{
public:
	RegexpClassifyLayer(TokenSource* input, const Config::Node& props);

	~RegexpClassifyLayer();

	Token* processToken(Token *t);

private:
	std::vector< std::pair<std::string, RegexMatcher*> > classifiers_;
};

#endif // REGEXPCLASSIFYLAYER_H
