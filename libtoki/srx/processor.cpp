#include "exception.h"
#include "processor.h"

#include <boost/foreach.hpp>

#include <unicode/regex.h>

#include <map>
#include <iostream>
#include <sstream>


namespace Toki { namespace Srx {


	Processor::Processor()
	{
	}

	void Processor::load_rules(const std::vector<Rule>& rules)
	{
		std::stringstream ss;
		std::vector<RegexMatcher*> r;
		BOOST_FOREACH (const Rule& r, rules) {
			std::stringstream ss;
			UErrorCode status = U_ZERO_ERROR;
			CompiledRule cr = r.compile(status);
			if (U_SUCCESS(status)) {
				crules_.push_back(cr);
			} else {
				throw Error("Rule failed to compile");
			}
		}
	}

	void Processor::compute_breaks(const UnicodeString& str, int length)
	{
		break_map_.clear();
		length_ = length;
		BOOST_FOREACH (const CompiledRule& cr, crules_) {
			cr.matcher->reset(str);
			while (cr.matcher->find()) {
				UErrorCode status = U_ZERO_ERROR;
				int n = cr.matcher->end(1, status);
				if (n < length) {
					break_map_t::value_type v(n, cr.breaks);
					break_map_.insert(v); //only insert if the index was not in the map
				} else {
					break;
				}
			}
		}
	}

	std::vector<bool> Processor::get_break_mask() const {
		std::vector<bool> breaks(length_);
		BOOST_FOREACH (break_map_t::value_type v, break_map_) {
			breaks[v.first] = v.second;
			std::cerr << v.first << ":" << v.second << " ";
		}
		return breaks;
	}

	std::vector<int> Processor::get_break_positions() const {
		std::vector<int> breaks;
		BOOST_FOREACH (break_map_t::value_type v, break_map_) {
			std::cerr << v.first << ":" << v.second << " ";
			if (v.second) {
				breaks.push_back(v.first);
			}
		}
		return breaks;
	}

} /* end ns Srx */ } /* end ns Toki */
