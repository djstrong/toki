#ifndef LIBTOKI_SRX_SRX_H
#define LIBTOKI_SRX_SRX_H

#include "document.h"
#include "unicodesource.h"

#include <boost/smart_ptr.hpp>


namespace Toki { namespace Srx {

	class SourceWrapper {
	public:
		SourceWrapper(UnicodeSource* s, int window = 200, int margin = 100);

		SourceWrapper(boost::shared_ptr<UnicodeSource> s, int window = 200, int margin = 100);

		/// Override from UnicodeSource
		UChar get_next_char();

		/// Override from UnicodeSource
		UChar peek_next_char();

		/// Override from UnicodeSource
		bool has_more_chars();

		/// Override from UnicodeSource
		bool peek_begins_sentence();

	private:
		void init();

		bool buffer_ok() {
			return out_ptr_ - buffer_ < buffer_size_;
		}

		void ensure_more();

		void move_buffer();

		void calculate_breaks();

		boost::shared_ptr<UnicodeSource> s_;
		int window_size_;
		int margin_size_;
		UChar* buffer_;
		UChar* out_ptr_;
		int buffer_size_;
		std::vector<bool> breaks_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_SRX_H
