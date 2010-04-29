#ifndef LIBTOKI_SRX_SRX_H
#define LIBTOKI_SRX_SRX_H

#include "document.h"
#include "processor.h"
#include "unicodesource.h"

#include <boost/smart_ptr.hpp>


namespace Toki { namespace Srx {

	class SourceWrapper : public UnicodeSource {
	public:
		SourceWrapper(UnicodeSource* s, const Processor& p,
				int window = 200, int margin = 100);

		SourceWrapper(boost::shared_ptr<UnicodeSource> s, const Processor& p,
				int window = 200, int margin = 100);

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
			return out_idx_ < buffer_size_ && out_idx_ < window_size_;
		}

		void ensure_more();

		void move_buffer();

		void calculate_breaks();

		boost::shared_ptr<UnicodeSource> s_;
		Processor proc_;
		int window_size_;
		int margin_size_;
		UChar* buffer_;
		int out_idx_;
		int buffer_size_;
		std::vector<bool> breaks_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_SRX_H
