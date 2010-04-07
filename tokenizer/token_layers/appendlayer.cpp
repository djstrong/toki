#include "appendlayer.h"
#include "token.h"
#include <boost/property_tree/ptree.hpp>

AppendLayer::AppendLayer(TokenSource *input, const Config::Node &props)
	: TokenLayer(input, props), append_()
{
	append_ = UnicodeString::fromUTF8(props.get("append", "!")).unescape();
}

std::string AppendLayer::info() const
{
	return "append";
}

Token* AppendLayer::processToken(Token* t)
{
	t->set_orth(t->orth() + append_);
	return t;
}
