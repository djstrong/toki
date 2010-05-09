#ifndef LIBTOKI_SRX_SEGMENTER_H
#define LIBTOKI_SRX_SEGMENTER_H

#include "rule.h"
#include <vector>
#include <map>

#include <unicode/regex.h>
#include <boost/regex/icu.hpp>

namespace Toki { namespace Srx {

	class Segmenter
	{
	public:
		Segmenter();

		virtual ~Segmenter();

		virtual void load_rules(const std::vector<Rule>& rules) = 0;

		virtual void compute_breaks(const UnicodeString& str, int from, int to) = 0;

		std::vector<bool> get_break_mask() const;

		std::vector<int> get_break_positions() const;

	protected:
		typedef std::map<int, bool> break_map_t;

		break_map_t break_map_;

		int length_;

	};

	class NaiveIcuSegmenter : public Segmenter
	{
	public:
		NaiveIcuSegmenter();

		void load_rules(const std::vector<Rule>& rules);

		virtual void compute_breaks(const UnicodeString& str, int from, int to);

		const std::vector<CompiledRule>& get_compiled_rules() const {
			return crules_;
		}

	private:
		std::vector<CompiledRule> crules_;
	};

	class NaiveBoostSegmenter : public Segmenter
	{
	public:
		NaiveBoostSegmenter();

		void load_rules(const std::vector<Rule>& rules);

		virtual void compute_breaks(const UnicodeString& str, int from, int to);
	private:
		std::vector< std::pair<boost::u32regex, bool> > crules_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_SEGMENTER_H
