#include "groupsplitlayer.h"
#include "token.h"

namespace Toki {

	GroupSplitLayer::GroupSplitLayer(TokenSource* input, const Config::Node& props)
		: BasicSplitLayer(input, props)
	{
	}

	std::string GroupSplitLayer::info() const
	{
		std::stringstream ss;
		ss << "group_split{" << separator_type()
			<< "|" << separators().size() << "}";
		return ss.str();
	}

	std::string GroupSplitLayer::long_info() const
	{
		return BasicSplitLayer::long_info() + " (group)";
	}


	void GroupSplitLayer::prepareMoreTokens(Token *t)
	{
		const UnicodeString& orth = t->orth();
		int i = 0;

		while (i < orth.length() && !isSplitChar(orth.charAt(i))) ++i;
		if (i == orth.length()) {
			enqueueOutputToken(t);
		} else {
			if (i > 0) {
				UnicodeString part;
				orth.extractBetween(0, i, part);
				Token* b = t->clone_changed(part);
				t->mark_as_cut();
				enqueueOutputToken(b);
			}

			int split_begin = i;
			int split_end = i;
			do {
				++i;
				while (i < orth.length() && isSplitChar(orth.charAt(i))) ++i;
				UnicodeString part;
				orth.extractBetween(split_begin, i, part);
				Token* s = t->clone_changed(part, separator_type());
				t->mark_as_cut();
				enqueueOutputToken(s);
				split_end = i;
				if (split_end < orth.length()) {
					++i;
					while (i < orth.length() && !isSplitChar(orth.charAt(i))) ++i;
					UnicodeString part;
					orth.extractBetween(split_end, i, part);
					Token* b = t->clone_changed(part);
					t->mark_as_cut();
					enqueueOutputToken(b);
					split_begin = i;
				}
			} while (i < orth.length());
			delete t;
		}
	}

} /* end ns Toki */
