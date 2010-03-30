#ifndef LEXICONCLASSIFYLAYER_H
#define LEXICONCLASSIFYLAYER_H

#include "tokenlayer.h"

#include <unicode/unistr.h>

#include <set>

template <typename CMP>
class LexiconClassifyLayer : public TokenLayer
{
public:
	LexiconClassifyLayer(TokenSource* input, const Config::Node& props);

	~LexiconClassifyLayer();

	Token* processToken(Token *t);

private:
	std::set<UnicodeString, CMP> lex_;
	std::string token_type_;
};


#include "token.h"
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>


template<typename CMP>
LexiconClassifyLayer<CMP>::LexiconClassifyLayer(TokenSource *input, const Config::Node &props)
	: TokenLayer(input, props), lex_(), token_type_()
{
	token_type_ = props.get<std::string>("token_type", "lex");
	std::vector<std::string> v;
	std::string sep(", ");
	const std::string& sepstring = props.get<std::string>("lexicon", "");
	boost::algorithm::split(v, sepstring, boost::is_any_of(sep));
	BOOST_FOREACH (const std::string& s, v) {
		if (!s.empty()) {
			lex_.insert(UnicodeString::fromUTF8(s).unescape());
		}
	}
}

template<typename CMP>
LexiconClassifyLayer<CMP>::~LexiconClassifyLayer()
{
}

template<typename CMP>
Token* LexiconClassifyLayer<CMP>::processToken(Token *t)
{
	if (lex_.find(t->orth()) != lex_.end()) {
		t->set_type(token_type_);
	}
	return t;
}

struct IcuStringCaselessCompare
{
public:
	bool operator()(const UnicodeString& u1, const UnicodeString& u2) {
		return u1.caseCompare(u2, 0) < 0;
	}
};

typedef LexiconClassifyLayer<
	std::less< UnicodeString >
> CaseLexiconClassifyLayer;

typedef LexiconClassifyLayer<
	IcuStringCaselessCompare
> CaselessLexiconClassifyLayer;



#endif // LEXICONCLASSIFYLAYER_H
