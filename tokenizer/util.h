#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <unicode/unistr.h>

namespace Util {

template <typename TContainer>
void utf8StringToUcharContainer(const std::string& s, TContainer& container)
{
	UnicodeString pres = UnicodeString::fromUTF8(s).unescape();
	for (int i = 0; i < pres.length(); ++i) {
		container.insert(pres.charAt(i));
	}
}

std::string unescape_utf8(const std::string& str);

} //end namespace Util

#endif // UTIL_H
