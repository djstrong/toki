#include "appendlayer.h"
#include "token.h"
#include <boost/property_tree/ptree.hpp>

AppendLayer::AppendLayer(TokenSource *input, const Properties &props)
	: TokenLayer(input, props), append_()
{
	append_ = UnicodeString::fromUTF8(props.get("append", "!")).unescape();
}

Token* AppendLayer::getNextToken()
{
	Token* t = getTokenFromInput();
	if (t) {
		if (shouldProcessTokenType(t->type())) {
			t->set_orth(t->orth() + append_);
		}
	}
	return t;
}

bool AppendLayer::registered = TokenLayer::register_layer<AppendLayer>("append");
