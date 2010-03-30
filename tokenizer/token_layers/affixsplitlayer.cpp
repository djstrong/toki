#include "affixsplitlayer.h"
#include "token.h"
#include "util.h"

AffixSplitLayer::AffixSplitLayer(TokenSource* input, const Config::Node& props)
	: OutputQueueLayer(input, props)
{
	prefix_type_ = props.get<std::string>("prefix_token_type", "pre");
	postfix_type_ = props.get<std::string>("postfix_token_type", "post");
	std::string prefixes = props.get("prefix_chars", "");
	Util::utf8StringToUcharContainer(prefixes, prefix_chars_);
	std::string postfixes = props.get("postfix_chars", "");
	Util::utf8StringToUcharContainer(postfixes, postfix_chars_);
}

void AffixSplitLayer::prepareMoreTokens(Token* t)
{
	int body_begin_index = 0;
	Token::WhitespaceAmount wa = t->preceeding_whitespace();
	while (body_begin_index < t->orth().length() && isPrefixChar(t->orth().charAt(body_begin_index))) {
		Token* pre = new Token(t->orth().charAt(body_begin_index), prefix_type_, wa);
		enqueueOutputToken(pre);
		wa = Token::WA_None;
		++body_begin_index;
	}
	int body_end_index = t->orth().length();
	while (body_end_index > body_begin_index && isPostfixChar(t->orth().charAt(body_end_index - 1))) {
		--body_end_index;
	}
	if (body_end_index > body_begin_index) {
		UnicodeString body_orth;
		t->orth().extractBetween(body_begin_index, body_end_index, body_orth);
		Token* body = new Token(body_orth, t->type(), wa);
		enqueueOutputToken(body);
		wa = Token::WA_None;
	}
	while (body_end_index < t->orth().length()) {
		Token* post = new Token(t->orth().charAt(body_end_index), postfix_type_, wa);
		enqueueOutputToken(post);
		wa = Token::WA_None;
		++body_end_index;
	}
	delete t;
}

bool AffixSplitLayer::isPrefixChar(UChar c)
{
	return prefix_chars_.find(c) != prefix_chars_.end();
}

bool AffixSplitLayer::isPostfixChar(UChar c)
{
	return postfix_chars_.find(c) != postfix_chars_.end();
}
