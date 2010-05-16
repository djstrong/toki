#include "exception.h"
#include "segmenter.h"
#include "../util.h"
#include "foreach.h"

#include <map>
#include <iostream>
#include <sstream>


namespace Toki { namespace Srx {


	Segmenter::Segmenter()
	{
	}

	Segmenter::~Segmenter()
	{
	}

	std::vector<bool> Segmenter::get_break_mask() const {
		std::vector<bool> breaks(length_);
		foreach (break_map_t::value_type v, break_map_) {
			breaks[v.first] = v.second;
		}
		return breaks;
	}

	std::vector<int> Segmenter::get_break_positions() const {
		std::vector<int> breaks;
		foreach (break_map_t::value_type v, break_map_) {
			if (v.second) {
				breaks.push_back(v.first);
			}
		}
		return breaks;
	}

	NaiveIcuSegmenter::NaiveIcuSegmenter()
	{
	}

	NaiveIcuSegmenter::~NaiveIcuSegmenter()
	{
		foreach (const CompiledRule& cr, crules_) {
			delete cr.matcher;
		}
	}

	void NaiveIcuSegmenter::load_rules(const std::vector<Rule>& rules)
	{
		foreach (const Rule& r, rules) {
			UErrorCode status = U_ZERO_ERROR;
			CompiledRule cr = r.compile(status);
			if (U_SUCCESS(status)) {
				crules_.push_back(cr);
			} else {
				std::stringstream ss;
				ss << r.before << " : " << r.after;
				throw Error("Rule failed to compile: " + ss.str());
			}
		}
	}

	void NaiveIcuSegmenter::compute_breaks(const UnicodeString& str, int from, int to)
	{
		//std::cerr << "SRXP run from " << from << " to " << to
		//		<< " on [" << Util::to_utf8(str) << "] :";
		break_map_.clear();
		to -= from;
		length_ = to;
		foreach (const CompiledRule& cr, crules_) {
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

	NaiveBoostSegmenter::NaiveBoostSegmenter()
	{
	}

	void NaiveBoostSegmenter::load_rules(const std::vector<Rule>& rules)
	{
		std::pair<boost::u32regex, bool> cr;
		foreach (const Rule& r, rules) {
			cr.first = boost::make_u32regex(r.create_pattern());
			cr.second = r.breaks;
			crules_.push_back(cr);
		}
	}

	void NaiveBoostSegmenter::compute_breaks(const UnicodeString& str, int from, int to)
	{
		//std::cerr << "SRXP run from " << from << " to " << to
		//		<< " on [" << Util::to_utf8(str) << "] :";
		break_map_.clear();
		to -= from;
		length_ = to;

		typedef std::pair<boost::u32regex, bool> cr_t;
		foreach (const cr_t& cr, crules_) {
			boost::match_results<const UChar*> what;
			const UChar* start = str.getBuffer();
			const UChar* end = start + str.length();
			boost::match_flag_type flags = boost::match_default;
			while (boost::u32regex_search(start, end, what, cr.first, flags)) {
				int n = what[1].second - str.getBuffer();
				n -= from;
				if (n >= 0) {
					if (n < to) {
						break_map_t::value_type v(n, cr.second);
						break_map_.insert(v); //only insert if the index was not in the map
					} else {
						break;
					}
				}
				start = what[0].first + 1; // sad panda
				flags |= boost::match_prev_avail;
				flags |= boost::match_not_bob;
			}
		}
		//std::vector<int> b = get_break_positions();
		//for (size_t i = 0; i < b.size(); ++i) {
		//	std::cerr << b[i] << " ";
		//}
		//std::cerr << "\n";
	}




} /* end ns Srx */ } /* end ns Toki */
