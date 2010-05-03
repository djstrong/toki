#include "exception.h"
#include "processor.h"
#include "../util.h"

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

	void Processor::compute_breaks(const UnicodeString& str, int from, int to)
	{
		//std::cerr << "SRXP run from " << from << " to " << to
		//		<< " on [" << Util::to_utf8(str) << "] :";
		break_map_.clear();
		to -= from;
		length_ = to;
		BOOST_FOREACH (const CompiledRule& cr, crules_) {
			UErrorCode ue = U_ZERO_ERROR;
			int i = 0;
			cr.matcher->reset(str);
			while (cr.matcher->find(i, ue)) {
				UErrorCode status = U_ZERO_ERROR;
				int n = cr.matcher->end(1, status);
				n -= from;
				if (n >= 0) {
					if (n < to) {
						break_map_t::value_type v(n, cr.breaks);
						break_map_.insert(v); //only insert if the index was not in the map
					} else {
						break;
					}
				}
				i = cr.matcher->start(status) + 1;
			}
		}
		//std::vector<int> b = get_break_positions();
		//for (size_t i = 0; i < b.size(); ++i) {
		//	std::cerr << b[i] << " ";
		//}
		//std::cerr << "\n";
	}

	std::vector<bool> Processor::get_break_mask() const {
		std::vector<bool> breaks(length_);
		BOOST_FOREACH (break_map_t::value_type v, break_map_) {
			breaks[v.first] = v.second;
		}
		return breaks;
	}

	std::vector<int> Processor::get_break_positions() const {
		std::vector<int> breaks;
		BOOST_FOREACH (break_map_t::value_type v, break_map_) {
			if (v.second) {
				breaks.push_back(v.first);
			}
		}
		return breaks;
	}

} /* end ns Srx */ } /* end ns Toki */
