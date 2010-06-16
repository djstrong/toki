#ifndef LIBTOKI_ICUSTRINGSOURCE_H
#define LIBTOKI_ICUSTRINGSOURCE_H
#include <unicode/unistr.h>
#include <unicode/schriter.h>

#include <libtoki/unicodesource.h>

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
		UChar peek_next_char();

		/// Override from UnicodeSource
		UChar get_next_char();

		/// Override from UnicodeSource
		bool has_more_chars();

	private:
		/// The internal StringCharacterIterator object
		StringCharacterIterator iter_;
	};

} /* end ns Toki */


#endif // LIBTOKI_ICUSTRINGSOURCE_H
