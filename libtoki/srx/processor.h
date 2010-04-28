#ifndef LIBTOKI_SRX_PROCESSOR_H
#define LIBTOKI_SRX_PROCESSOR_H

#include "rule.h"
#include <vector>
#include <map>

namespace Toki { namespace Srx {

	class Processor
	{
	public:
		Processor();

		void load_rules(const std::vector<Rule>& rules);

		void compute_breaks(const UnicodeString& str, int length);

		std::vector<bool> get_break_mask() const;

		std::vector<int> get_break_positions() const;
	private:
		typedef std::map<int, bool> break_map_t;

		break_map_t break_map_;

		int length_;

		std::vector<CompiledRule> crules_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_PROCESSOR_H
