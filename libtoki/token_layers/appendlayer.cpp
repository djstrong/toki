#include "appendlayer.h"
#include "token.h"
#include "util.h"
#include <boost/property_tree/ptree.hpp>

namespace Toki {

	AppendLayer::AppendLayer(TokenSource *input, const Config::Node &props)
		: TokenLayer(input, props), append_()
	{
		append_ = UnicodeString::fromUTF8(props.get("append", "!")).unescape();
	}

	std::string AppendLayer::info() const
	{
		return "append";
	}

	std::string AppendLayer::long_info() const
	{
		return TokenLayer::long_info() + ", append: " + Util::to_utf8(append_);
	}

	Token* AppendLayer::processToken(Token* t)
	{
		t->set_orth(t->orth() + append_);
		return t;
	}

} /* end namespace Toki */
