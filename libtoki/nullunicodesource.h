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
		UChar peekNextChar() {
			throw TokenizerImpossibleError("NullUnicodeSource::peekNextChar called");
			return 0;
		}

		/// UnicodeSource override
		UChar getNextChar() {
			throw TokenizerImpossibleError("NullUnicodeSource::getNextChar called");
			return 0;
		}

		/// UnicodeSource override
		bool hasMoreChars() {
			return false;
		}
	};

} /* end ns Toki */

#endif // LIBTOKI_NULLUNICODESOURCE_H
