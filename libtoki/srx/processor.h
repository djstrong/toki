#ifndef LIBTOKI_SRX_PROCESSOR_H
#define LIBTOKI_SRX_PROCESSOR_H

#include "rule.h"
#include <vector>

namespace Toki { namespace Srx {

	class Processor
	{
	public:
		Processor();

		void load_rules(const std::vector<Rule>& rules);
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_PROCESSOR_H
