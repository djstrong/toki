#ifndef LIBTOKI_NULLUNICODESOURCE_H
#define LIBTOKI_NULLUNICODESOURCE_H

#include "unicodesource.h"

#include "exception.h"

namespace Toki {
	/**
	 * A null UnicodeSource that never returns anything and always claims there are
	 * no more characters. Will throw when peek/get next char is requested.
	 */
	class NullUnicodeSource : public UnicodeSource
	{
	public:
		/// The constructor
		NullUnicodeSource() {}

		/// UnicodeSource override
		UChar peek_next_char() {
			throw TokenizerImpossibleError("NullUnicodeSource::peek_next_char called");
			return 0;
		}

		/// UnicodeSource override
		UChar get_next_char() {
			throw TokenizerImpossibleError("NullUnicodeSource::get_next_char called");
			return 0;
		}

		/// UnicodeSource override
		bool has_more_chars() {
			return false;
		}
	};

} /* end ns Toki */

#endif // LIBTOKI_NULLUNICODESOURCE_H
