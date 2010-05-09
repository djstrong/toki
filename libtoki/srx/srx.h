#ifndef LIBTOKI_SRX_SRX_H
#define LIBTOKI_SRX_SRX_H

#include "document.h"
#include "segmenter.h"
#include "unicodesource.h"

#include <boost/smart_ptr.hpp>
#include <boost/utility.hpp>


namespace Toki { namespace Srx {

	/**
	 * A SRX parser wrapping a UnicodeSource.
	 *
	 * Characters from the wrapped source are put in a buffer, treated as
	 * a "window" with margins one each side (so the total size of the buffer
	 * is window + margin * 2. SRX sentence breaks that happen to lay inside
	 * the window are computed and later available through the UnicodeSource
	 * overriden peek_begins_sentence().
	 *
	 * The buffer layout is: left_margin window right_margin
	 *
	 * Initially, the left buffer is empty.
	 *
	 * Note that this class does not understand SRX, it just takes a SRX
	 * segmenter and runs it repeatedly on a buffer. Characters are always
	 * returned from the window area of the buffer, advancing the internal
	 * pointer. When the pointer starts pointing to the beginning of the right
	 * margin, the buffer is moved so that the last margin_width characters of
	 * the window form the new left margin, and new characters are streamed
	 * from the wrapped source. SRX segment breaks are then computed again and
	 * the internal pointer is reset to point at the beginning of the window.
	 *
	 * Larger windows should yield more performance, and large margin sizes will
	 * result in preformance drop. However, the margin size must be large
	 * enough to contain the longest regex match expected, otherwise results may
	 * be off. Technically the restriction is slightly more loose, but the
	 * aforementioned rule of thumb is reasonable anyway.
	 */
	class SourceWrapper : public UnicodeSource, private boost::noncopyable {
	public:
		/**
		 * Constructor for the SRX UnicodeSource wrapper.
		 * Takes ownerhip of the wrapped source (through a shared pointer)
		 */
		SourceWrapper(UnicodeSource* s, int window = 200, int margin = 100);

		SourceWrapper(boost::shared_ptr<UnicodeSource> s,
				int window = 200, int margin = 100);

		~SourceWrapper();

		/// Override from UnicodeSource
		UChar get_next_char();

		/// Override from UnicodeSource
		UChar peek_next_char();

		/// Override from UnicodeSource
		bool has_more_chars();

		/// Override from UnicodeSource
		bool peek_begins_sentence();

		/**
		 * Setter for the SRX segmenter object -- raw pointer version.
		 * Takes ownership of the segmenter.
		 */
		void set_segmenter(Segmenter* s);

		/**
		 * Setter for the SRX segmenter object -- shared pointer version.
		 */
		void set_segmenter(boost::shared_ptr<Segmenter> s);

		/**
		 * Setter for the wrapped source object -- raw pointer version.
		 * Takes ownership of the source.
		 */
		void set_source(UnicodeSource* s);

		/**
		 * Setter for the wrapped source object -- shared pointer version.
		 */
		void set_source(boost::shared_ptr<UnicodeSource> s);

		boost::shared_ptr<Segmenter> get_segmenter() const {
			return segmenter_;
		}

	private:
		void init();

		bool buffer_ok() {
			return (out_idx_ < buffer_end_idx_) && (out_idx_ < window_size_ + margin_size_);
		}

		void init_buffer();

		void ensure_more();

		void move_buffer();

		void calculate_breaks();

		boost::shared_ptr<UnicodeSource> source_;
		boost::shared_ptr<Segmenter> segmenter_;
		int window_size_;
		int margin_size_;
		int buffer_size_;
		UChar* buffer_;
		int out_idx_;
		int buffer_start_idx_;
		int buffer_end_idx_;
		std::vector<bool> breaks_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_SRX_H
