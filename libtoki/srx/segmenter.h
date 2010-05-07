#ifndef LIBTOKI_SRX_SEGMENTER_H
#define LIBTOKI_SRX_SEGMENTER_H

#include "rule.h"
#include <vector>
#include <map>

namespace Toki { namespace Srx {

	class Segmenter
	{
	public:
		Segmenter();

		void load_rules(const std::vector<Rule>& rules);

		const std::vector<CompiledRule>& get_compiled_rules() const {
			return crules_;
		}

		void compute_breaks(const UnicodeString& str, int from, int to);

		std::vector<bool> get_break_mask() const;

		std::vector<int> get_break_positions() const;
	private:
		typedef std::map<int, bool> break_map_t;

		break_map_t break_map_;

		int length_;

		std::vector<CompiledRule> crules_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_SEGMENTER_H
