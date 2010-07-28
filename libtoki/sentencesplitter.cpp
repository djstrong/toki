#include <libtoki/sentencesplitter.h>

namespace Toki {

	SentenceSplitter::SentenceSplitter(TokenSource& ts)
		: ts_(&ts), buf_(NULL)
	{
	}

	SentenceSplitter::~SentenceSplitter()
	{
		delete buf_;
	}

	void SentenceSplitter::set_source(TokenSource &ts)
	{
		ts_ = &ts;
	}

	Token* SentenceSplitter::get_buf()
	{
		Token* tmp = buf_;
		buf_ = NULL;
		return tmp;
	}

	bool SentenceSplitter::has_more()
	{
		if (buf_ != NULL) return true;
		buf_ = source().get_next_token();
		return buf_ != NULL;
	}

	std::vector<Token*> SentenceSplitter::get_next_sentence()
	{
		std::vector<Token*> sentence;
		if (buf_ == NULL) {
			buf_ = source().get_next_token();
		}
		if (buf_) {
			sentence.push_back(buf_);
			buf_ = source().get_next_token();
			while (buf_ != NULL && !buf_->begins_sentence()) {
				sentence.push_back(buf_);
				buf_ = source().get_next_token();
			}
		}
		return sentence;
	}

} /* end ns Toki */
