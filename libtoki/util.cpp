#include "util.h"

namespace Toki { namespace Util {

	std::string unescape_utf8(const std::string& str)
	{
		std::string out;
		UnicodeString u = UnicodeString::fromUTF8(str).unescape();
		u.toUTF8String(out);
		return out;
	}

	std::string to_utf8(const UnicodeString &ustr)
	{
		std::string s;
		ustr.toUTF8String(s);
		return s;
	}

} /* end namespace Util */ } /* end namespace Toki */
