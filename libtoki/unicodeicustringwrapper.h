#ifndef ICUSTRINGSOURCE_H
#define ICUSTRINGSOURCE_H
#include <unicode/unistr.h>
#include <unicode/schriter.h>

#include "unicodesource.h"

namespace Toki {

	/**
	 * A thin wrapper around UnicodeString (using aStringCharacterIterator) to adapt
	 * it to the UnicodeSource interface.
	 */
	class UnicodeIcuStringWrapper : public UnicodeSource
	{
	public:
		/**
		 * The constructor.
		 *
		 * @param u The Unicode string to wrap. The string is copied.
		 */
		UnicodeIcuStringWrapper(const UnicodeString& u);

		/// The destructor
		~UnicodeIcuStringWrapper();

		/// Override from UnicodeSource
		UChar peekNextChar();

		/// Override from UnicodeSource
		UChar getNextChar();

		/// Override from UnicodeSource
		bool hasMoreChars();

	private:
		/// The internal StringCharacterIterator object
		StringCharacterIterator iter_;
	};

} /* end ns Toki */


#endif // ICUSTRINGSOURCE_H
