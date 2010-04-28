#include "rule.h"

#include <sstream>

namespace Toki { namespace Srx {

	std::string Rule::create_lookbehind_pattern() const {
		std::stringstream ss;
		return ss.str();
	}

} /* end ns Srx */ } /* end ns Toki */
