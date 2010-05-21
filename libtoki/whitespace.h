#ifndef LIBTOKI_WHITESPACE_H
#define LIBTOKI_WHITESPACE_H

#include <string>

namespace Toki {

	/**
	 * A single token being processed. The orth is stored as an ICU UnicodeString.
	 */
	namespace Whitespace
	{
		enum Enum {
			None,
			Space,
			ManySpaces,
			Newline,
			ManyNewlines,
			PostLast // last item guard
		};

		std::string to_string(Enum wa);

		Enum from_string(const std::string& s);
	} /* end ns Toki */

}
#endif // LIBTOKI_WHITESPACE_H
