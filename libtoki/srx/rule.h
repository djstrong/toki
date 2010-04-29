#ifndef LIBTOKI_SRX_RULE_H
#define LIBTOKI_SRX_RULE_H

#include <string>

#include <unicode/regex.h>

namespace Toki { namespace Srx {

	struct CompiledRule
	{
		RegexMatcher* matcher;
		bool breaks;
	};

	struct Rule
	{
		std::string before;
		std::string after;
		bool breaks;

		std::string create_lookbehind_pattern() const;

		CompiledRule compile(UErrorCode& ue) const;
	};


} /* end ns Srx */ } /* end ns Toki */

#endif // RULE_H
