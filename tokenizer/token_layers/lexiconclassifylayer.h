#ifndef LEXICONCLASSIFYLAYER_H
#define LEXICONCLASSIFYLAYER_H

#include "tokenlayer.h"

#include <unicode/unistr.h>

#include <set>

class LexiconClassifyLayer : public TokenLayer
{
public:
	LexiconClassifyLayer(TokenSource* input, const Config::Node& props);

	~LexiconClassifyLayer();

	Token* processToken(Token *t);

private:
	std::set<UnicodeString> lex_;
	std::string token_type_;
};

#endif // LEXICONCLASSIFYLAYER_H
