#include "basicsplitlayer.h"
#include "token.h"
#include "util.h"

namespace Toki {

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

	std::string BasicSplitLayer::long_info() const
	{
		std::stringstream ss;
		ss << ", split: " << split_chars_.size() << " separators, type " << sep_type_;
		return OutputQueueLayer::long_info() + ss.str();
	}

	void BasicSplitLayer::prepareMoreTokens(Token* t)
	{
		const UnicodeString& orth = t->orth();
		int splitfrom = 0;
		for (int i = 0; i < orth.length(); ++i) {
			if (isSplitChar(orth.charAt(i))) {
				if (i > splitfrom) {
					UnicodeString part;
					orth.extractBetween(splitfrom, i, part);
					Token* pre = t->clone_changed(part);
					t->mark_as_cut();
					enqueueOutputToken(pre);
				}
				Token* sep = t->clone_changed(orth.charAt(i), sep_type_);
				t->mark_as_cut();
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
				t->set_orth(part);
				enqueueOutputToken(t);
			} else {
				delete t;
			}
		}
	}

	bool BasicSplitLayer::isSplitChar(UChar c)
	{
		return split_chars_.find(c) != split_chars_.end();
	}

} /* end namespace Toki */
