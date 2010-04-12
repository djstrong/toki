#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <unicode/unistr.h>

namespace Toki { namespace Util {

	/**
	 * Helper function to put all characters from a std::string and put them in a
	 * (set-like) container. The string is converted to a UnicodeString, unescaping
	 * is performed and UChars are fed into the container.
	 */
	template <typename TContainer>
	void utf8StringToUcharContainer(const std::string& s, TContainer& container)
	{
		UnicodeString pres = UnicodeString::fromUTF8(s).unescape();
		for (int i = 0; i < pres.length(); ++i) {
			container.insert(pres.charAt(i));
		}
	}

	/**
	 * Helper function to 'unescape' an UTF8 string, which is done by converting
	 * to a UnicodeString, ICU-unescaping and converting back to UTF8.
	 */
	std::string unescape_utf8(const std::string& str);

} /* end ns Util */ } /* end ns Toki */

#endif // UTIL_H
