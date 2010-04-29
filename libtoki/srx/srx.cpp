#include "srx.h"
#include "processor.h"

namespace Toki { namespace Srx {

	SourceWrapper::SourceWrapper(UnicodeSource *s, const Processor& p,
			int window, int margin)
		: s_(s), proc_(p), window_size_(window), margin_size_(margin)
		, buffer_(NULL), out_idx_(0), buffer_size_(0), breaks_(window_size_)
	{
	}

	SourceWrapper::SourceWrapper(boost::shared_ptr<UnicodeSource>s,
			const Processor& p, int window, int margin)
		: s_(s), proc_(p), window_size_(window), margin_size_(margin)
		, buffer_(NULL), out_idx_(0), buffer_size_(0), breaks_(window_size_)
	{
	}

	UChar SourceWrapper::peek_next_char()
	{
		ensure_more();
		if (buffer_ok()) {
			return buffer_[out_idx_];
		} else {
			return 0;
		}
	}

	UChar SourceWrapper::get_next_char()
	{
		ensure_more();
		if (buffer_ok()) {
			return buffer_[out_idx_];
		} else {
			return 0;
		}
	}

	bool SourceWrapper::has_more_chars()
	{
		ensure_more();
		return buffer_ok();
	}

	bool SourceWrapper::peek_begins_sentence()
	{
		ensure_more();
		if (buffer_ok()) {
			return breaks_[out_idx_];
		} else {
			return false;
		}
	}

	void SourceWrapper::ensure_more()
	{
		if (!buffer_ok()) {
			move_buffer();
			calculate_breaks();
		}
	}

	void SourceWrapper::move_buffer()
	{

		int i = 0;
		while (i + window_size_ < buffer_size_) {
			buffer_[i] = buffer_[i + window_size_];
			++i;
		}
		while (i < window_size_ + margin_size_ && s_->has_more_chars()) {
			buffer_[i] = s_->get_next_char();
			++i;
		}
		buffer_size_ = i;
	}

	void SourceWrapper::calculate_breaks()
	{
		Processor proc;
		proc.compute_breaks(UnicodeString(false, buffer_, window_size_ + margin_size_), window_size_);
		breaks_ = proc.get_break_mask();
	}

} /* end ns Srx */ } /* end ns Toki */
