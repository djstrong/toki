#include "lexiconclassifylayer.h"
#include "token.h"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

LexiconClassifyLayer::LexiconClassifyLayer(TokenSource *input, const Config::Node &props)
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

LexiconClassifyLayer::~LexiconClassifyLayer()
{
}

Token* LexiconClassifyLayer::processToken(Token *t)
{
	if (lex_.find(t->orth()) != lex_.end()) {
		t->set_type(token_type_);
	}
	return t;
}
