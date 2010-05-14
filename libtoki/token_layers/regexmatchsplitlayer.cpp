#include "regexmatchsplitlayer.h"
#include "token.h"

namespace Toki {

	RegexMatchSplitLayer::RegexMatchSplitLayer(TokenSource *input, const Config::Node &props)
		: OutputQueueLayer(input, props), regex_(NULL), sep_type_()
	{
		UErrorCode status = U_ZERO_ERROR;
		regex_ = new RegexMatcher(UnicodeString::fromUTF8(props.get("regex", "")), 0, status);
		if (!U_SUCCESS(status)) {
			if (error_stream_) {
				(*error_stream_) << "Invalid regex: " << props.get("regex", "") << "\n";
			}
			regex_ = NULL;
		}
		sep_type_ = props.get<std::string>("separator_token_type", "sep");
	}

	std::string RegexMatchSplitLayer::info() const
	{
		std::stringstream ss;
		ss << "regex_m_split{" << sep_type_ << "}";
		if (regex_ == NULL) {
			ss << "<<REGEX INVALID>>";
		}
		return ss.str();
	}

	std::string RegexMatchSplitLayer::long_info() const
	{
		std::stringstream ss;
		ss << ", regex_match_split: type " << sep_type_;
		if (regex_ == NULL) {
			ss << " <<REGEX INVALID>>";
		}
		return OutputQueueLayer::long_info() + ss.str();
	}

	void RegexMatchSplitLayer::prepare_more_tokens(Token *t)
	{
		regex_->reset(t->orth());
		int start = 0;
		UErrorCode status = U_ZERO_ERROR;
		while (regex_->find(start, status)) {
			UErrorCode status2 = U_ZERO_ERROR;
			int match_start = regex_->start(status2);
			int match_end = regex_->end(status2);
			if (match_start > start) {
				//extract the part between start and match_start with the
				//original token type
				UnicodeString part;
				t->orth().extractBetween(start, match_start, part);
				enqueue_output_token(t->clone_changed(part));
				t->mark_as_cut();
			}
			//extract the matching region
			enqueue_output_token(t->clone_changed(regex_->group(0, status2), separator_type()));
			t->mark_as_cut();
			start = match_end;
		}
		if (start == 0) {
			//special case: regex did not match -- just pass the token through
			enqueue_output_token(t);
		} else {
			//something did match, check if anything is left at the end of the
			//token's orth
			if (start < t->orth().length()) {
				UnicodeString new_orth;
				t->orth().extractBetween(start, t->orth().length(), new_orth);
				t->set_orth(new_orth);
				enqueue_output_token(t);
			} else {
				delete t;
			}
		}
	}

} /* end ns Toki */
