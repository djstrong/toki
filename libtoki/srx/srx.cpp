#include "srx.h"
#include "segmenter.h"
#include "../util.h"

#include <iostream>

namespace Toki { namespace Srx {

	SourceWrapper::SourceWrapper(UnicodeSource *src, Segmenter* segm,
			int window, int margin)
		: source_(src), segmenter_(segm)
		, window_size_(window), margin_size_(margin)
		, buffer_size_(window_size_ + margin_size_ * 2)
		, buffer_(new UChar[buffer_size_])
		, out_idx_(margin_size_)
		, buffer_start_idx_(margin_size_), buffer_end_idx_(margin_size_)
		, breaks_(window_size_)
	{
		init_buffer();
	}

	SourceWrapper::SourceWrapper(boost::shared_ptr<UnicodeSource> src,
			boost::shared_ptr<Segmenter> segm, int window, int margin)
		: source_(src), segmenter_(segm)
		, window_size_(window), margin_size_(margin)
		, buffer_size_(window_size_ + margin_size_ * 2)
		, buffer_(new UChar[buffer_size_])
		, out_idx_(margin_size_)
		, buffer_start_idx_(margin_size_), buffer_end_idx_(margin_size_)
		, breaks_(window_size_)
	{
		init_buffer();
	}

	SourceWrapper::~SourceWrapper()
	{
		delete [] buffer_;
	}

	void SourceWrapper::set_segmenter(Segmenter *s)
	{
		std::cerr << "set_segmenter(*)\n";
		set_segmenter(boost::shared_ptr<Segmenter>(s));
	}

	void SourceWrapper::set_segmenter(boost::shared_ptr<Segmenter> s)
	{
		std::cerr << "set_segmenter(shared)\n";
		segmenter_ = s;
	}

	void SourceWrapper::set_source(UnicodeSource *s)
	{
		set_source(boost::shared_ptr<UnicodeSource>(s));
	}

	void SourceWrapper::set_source(boost::shared_ptr<UnicodeSource> s)
	{
		source_ = s;
		out_idx_ = margin_size_;
		buffer_start_idx_ = buffer_end_idx_ = margin_size_;
		init_buffer();
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
			return buffer_[out_idx_++];
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
			return breaks_[out_idx_ - margin_size_];
		} else {
			return false;
		}
	}

	void SourceWrapper::ensure_more()
	{
		//std::cerr << ".";
		if (!buffer_ok()) {
			//std::cerr << "ensure_more needs more " << out_idx_
			//		<< " " << buffer_start_idx_
			//		<< " " << buffer_end_idx_ << "\n";
			move_buffer();
			if (buffer_ok()) {
				calculate_breaks();
			}
		}
	}

	void SourceWrapper::init_buffer()
	{
		while (buffer_end_idx_ < buffer_size_ && source_->has_more_chars()) {
			buffer_[buffer_end_idx_] = source_->get_next_char();
			++buffer_end_idx_;
		}
		//std::cerr << "init buffer: " << Util::to_utf8(buffer_ + buffer_start_idx_)
		//		<< " " << buffer_start_idx_ << "\n";
		calculate_breaks();
	}

	void SourceWrapper::move_buffer()
	{
		//std::cerr << "B";
		int ii = window_size_;
		int io = 0;
		while (ii < buffer_end_idx_) {
			buffer_[io] = buffer_[ii];
			++io;
			++ii;
		}
		while (io < buffer_size_ && source_->has_more_chars()) {
			buffer_[io] = source_->get_next_char();
			++io;
		}
		buffer_start_idx_ = std::max(0, buffer_start_idx_ - window_size_);
		buffer_end_idx_ = io;
		out_idx_ = margin_size_;
	}

	void SourceWrapper::calculate_breaks()
	{
		if (!segmenter_) {
			std::cerr << "No segmenter in srx source wrapper\n";
			return;
		}
		UChar* bbegin = buffer_ + buffer_start_idx_;
		int blen = buffer_end_idx_ - buffer_start_idx_;
		int from = margin_size_ - buffer_start_idx_;
		int to = std::min(buffer_end_idx_, window_size_ + margin_size_);
		//std::cerr << margin_size_ << "/" << window_size_ << "/";
		//std::cerr << "ZZ" << buffer_start_idx_ << "-" << buffer_end_idx_ << " ";
		//if (buffer_end_idx_ > buffer_start_idx_) {
		//	std::cerr << Util::to_utf8(UnicodeString(false, bbegin, blen));
		//}
		//std::cerr << "\n";
		segmenter_->compute_breaks(UnicodeString(false, bbegin, blen), from, to);
		breaks_ = segmenter_->get_break_mask();
	}

} /* end ns Srx */ } /* end ns Toki */
