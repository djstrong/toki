#include "appendlayer.h"
#include "token.h"
#include <boost/property_tree/ptree.hpp>

AppendLayer::AppendLayer(TokenSource *input, const Properties &props)
	: TokenLayer(input, props), append_()
{
	append_ = UnicodeString::fromUTF8(props.get("append", "!")).unescape();
}

Token* AppendLayer::processToken(Token* t)
{
	t->set_orth(t->orth() + append_);
	return t;
}
