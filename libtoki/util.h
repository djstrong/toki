#ifndef LIBTOKI_UTIL_H
#define LIBTOKI_UTIL_H

#include <string>
#include <unicode/unistr.h>
#include <unicode/uniset.h>
#include <iostream>

namespace Toki { namespace Util {

	/**
	 * Helper function to 'unescape' an UTF8 string, which is done by converting
	 * to a UnicodeString, ICU-unescaping and converting back to UTF8.
	 */
	std::string unescape_utf8(const std::string& str);

	/**
	 * Helper function to convert an UnicodeString to a UTF-8 std::string
	 */
	std::string to_utf8(const UnicodeString& ustr);

	/**
	 * Helper function to put all characters from a std::string and put them in a
	 * (set-like) container. The string is converted to a UnicodeString, unescaping
	 * is performed and UChars are fed into the container. As a special case,
	 * if the string starts with a '[' character, ends with ']' and is more
	 * than two characters long it is treated like a ICU-style UnicodeSet
	 * e.g. [a-zA-Z_] and parsed as such using ICU facilities. This allows
	 * sepcyfying Unicode properties of the characters and more, see
	 * http://userguide.icu-project.org/strings/unicodeset for details.
	 */
	template <typename TContainer>
	void utf8_string_to_uchar_container(const std::string& s, TContainer& container)
	{
		UnicodeString pres = UnicodeString::fromUTF8(s);
		if (pres.length() > 2 && pres.startsWith("[") && pres.endsWith("]")) {
			UErrorCode status = U_ZERO_ERROR;
			UnicodeSet uset(pres, status);
			if (!U_SUCCESS(status)) {
				std::cerr << "Unicode character set invalid: " << s << " \n";
			} else {
				for (int i = 0; i < uset.size(); ++i) {
					container.insert(uset.charAt(i));
				}
			}
		} else {
			pres = pres.unescape();
			for (int i = 0; i < pres.length(); ++i) {
				container.insert(pres.charAt(i));
			}
		}
	}
} /* end ns Util */ } /* end ns Toki */

#endif // LIBTOKI_UTIL_H
