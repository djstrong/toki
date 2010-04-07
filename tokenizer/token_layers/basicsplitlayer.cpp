#include "basicsplitlayer.h"
#include "token.h"
#include "util.h"

BasicSplitLayer::BasicSplitLayer(TokenSource* input, const Config::Node& props)
	: OutputQueueLayer(input, props), split_chars_(), sep_type_()
{
	sep_type_ = props.get<std::string>("separator_token_type", "sep");
	std::string separators = props.get("separators", "");
	Util::utf8StringToUcharContainer(separators, split_chars_);
}

std::string BasicSplitLayer::info() const
{
	std::stringstream ss;
	ss << "split{" << sep_type_ << "|" << split_chars_.size() << "}";
	return ss.str();
}

void BasicSplitLayer::prepareMoreTokens(Token* t)
{
	const UnicodeString& orth = t->orth();
	int splitfrom = 0;
	Token::WhitespaceAmount wa = t->preceeding_whitespace();
	for (int i = 0; i < orth.length(); ++i) {
		if (isSplitChar(orth.charAt(i))) {
			UnicodeString part;
			orth.extractBetween(splitfrom, i, part);
			Token* pre = new Token(part, t->type(), wa);
			wa = Token::WA_None;
			Token* sep = new Token(orth.charAt(i), sep_type_, wa);
			enqueueOutputToken(pre);
			enqueueOutputToken(sep);
			splitfrom = i + 1;
		}
	}
	if (splitfrom == 0) {
		enqueueOutputToken(t);
	} else {
		if (splitfrom < orth.length()) {
			UnicodeString part;
			orth.extractBetween(splitfrom, orth.length(), part);
			Token* rest = new Token(part, t->type(), wa);
			enqueueOutputToken(rest);
		}
		delete t;
	}
}

bool BasicSplitLayer::isSplitChar(UChar c)
{
	return split_chars_.find(c) != split_chars_.end();
}
