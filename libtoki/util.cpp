#include "util.h"

namespace Toki { namespace Util {

	std::string unescape_utf8(const std::string& str)
	{
		std::string out;
		UnicodeString u = UnicodeString::fromUTF8(str).unescape();
		u.toUTF8String(out);
		return out;
	}

} /* end namespace Util */ } /* end namespace Toki */
