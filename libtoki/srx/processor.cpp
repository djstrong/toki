#include "processor.h"
#include <boost/foreach.hpp>

#include <unicode/regex.h>

#include <sstream>


namespace Toki { namespace Srx {


	void Processor::load_rules(const std::vector<Rule>& rules)
	{
		std::stringstream merged_no_break;
		bool merged_empty = true;
		std::vector<RegexMatcher*> r;
		BOOST_FOREACH (const Rule& r, rules) {
			UErrorCode status = U_ZERO_ERROR;
			if (r.breaks) {
				//RegexMatcher *m = new RegexMatcher(UnicodeString::fromUTF8(v.second.data()), 0, status);
				if (U_SUCCESS(status)) {
					//classifiers_.push_back(std::make_pair(type, m));
				}
			} else {
				if (!merged_empty) {
					merged_no_break << "|";
				} else {
					merged_empty = false;
				}
				merged_no_break << r.create_lookbehind_pattern();
			}

		}
	}

} /* end ns Srx */ } /* end ns Toki */
