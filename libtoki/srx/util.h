#ifndef LIBTOKI_SRX_UTIL_H
#define LIBTOKI_SRX_UTIL_H

#include <string>

namespace Toki { namespace Srx {

	namespace Util {

		std::string unquote_regex(const std::string& re);

		std::string prepare_regex_for_lookbehind(const std::string& re, int max_lookbehind);

	} /* end ns Util */

} /* end ns Srx */ } /* end ns Toki */


#endif // UTIL_H
