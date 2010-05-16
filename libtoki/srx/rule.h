#ifndef LIBTOKI_SRX_RULE_H
#define LIBTOKI_SRX_RULE_H

#include <string>

#include <unicode/regex.h>

namespace Toki { namespace Srx {

	/// Simple struct to hold a regex matcher and a bool flag
	struct CompiledRule
	{
		RegexMatcher* matcher;
		bool breaks;
	};

	/// SImple struct to hold the before and after patterns and the break flag
	struct Rule
	{
		/// the SRX rule "before" regex pattern
		std::string before;

		/// the SRX rule "after" regex pattern
		std::string after;

		/// the SRX rule "breaks" parameter
		bool breaks;

		std::string create_lookbehind_pattern() const;

		/// combine the patterns into a grouped single pattern
		UnicodeString create_pattern() const;

		/// compile the rule
		CompiledRule compile(UErrorCode& ue) const;
	};


} /* end ns Srx */ } /* end ns Toki */

#endif // RULE_H
