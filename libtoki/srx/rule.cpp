#include "rule.h"

#include <sstream>
#include <unicode/regex.h>

namespace Toki { namespace Srx {

	std::string Rule::create_lookbehind_pattern() const {
		std::stringstream ss;
		return ss.str();
	}

	UnicodeString Rule::create_pattern() const
	{
		std::stringstream ss;
		ss << "(" << before << ")(" << after << ")";
		return UnicodeString::fromUTF8(ss.str());
	}

	CompiledRule Rule::compile(UErrorCode& ue) const
	{
		CompiledRule cr;
		cr.matcher = new RegexMatcher(create_pattern(), 0, ue);
		cr.breaks = breaks;
		return cr;
	}

} /* end ns Srx */ } /* end ns Toki */
