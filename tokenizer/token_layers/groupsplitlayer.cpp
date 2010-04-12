#include "groupsplitlayer.h"
#include "token.h"

namespace Toki {

	GroupSplitLayer::GroupSplitLayer(TokenSource* input, const Config::Node& props)
		: BasicSplitLayer(input, props)
	{
	}

	void GroupSplitLayer::prepareMoreTokens(Token *t)
	{
		const UnicodeString& orth = t->orth();
		Token::WhitespaceAmount wa = t->preceeding_whitespace();
		int i = 0;

		while (i < orth.length() && !isSplitChar(orth.charAt(i))) ++i;
		if (i == orth.length()) {
			enqueueOutputToken(t);
		} else {
			if (i > 0) {
				UnicodeString part;
				orth.extractBetween(0, i, part);
				Token* b = new Token(part, t->type(), wa);
				wa = Token::WA_None;
				enqueueOutputToken(b);
			}

			int split_begin = i;
			int split_end = i;
			do {
				++i;
				while (i < orth.length() && isSplitChar(orth.charAt(i))) ++i;
				UnicodeString part;
				orth.extractBetween(split_begin, i, part);
				Token* s = new Token(part, separator_type(), wa);
				wa = Token::WA_None;
				enqueueOutputToken(s);
				split_end = i;
				if (split_end < orth.length()) {
					++i;
					while (i < orth.length() && !isSplitChar(orth.charAt(i))) ++i;
					UnicodeString part;
					orth.extractBetween(split_end, i, part);
					Token* b = new Token(part, t->type(), wa);
					wa = Token::WA_None;
					enqueueOutputToken(b);
					split_begin = i;
				}
			} while (i < orth.length());
			delete t;
		}
	}

} /* end ns Toki */
