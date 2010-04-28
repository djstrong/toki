#include "rule.h"

#include <sstream>
#include <unicode/regex.h>

namespace Toki { namespace Srx {

	std::string Rule::create_lookbehind_pattern() const {
		std::stringstream ss;
		return ss.str();
	}

	CompiledRule Rule::compile(UErrorCode& ue) const
	{
		std::stringstream ss;
		ss << "(" << before << ")(" << after << ")";
		CompiledRule cr;
		cr.matcher = new RegexMatcher(UnicodeString::fromUTF8(ss.str()), 0, ue);
		cr.breaks = breaks;
		return cr;
	}

} /* end ns Srx */ } /* end ns Toki */
