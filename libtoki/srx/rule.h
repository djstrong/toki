#ifndef LIBTOKI_SRX_RULE_H
#define LIBTOKI_SRX_RULE_H

#include <string>

namespace Toki { namespace Srx {

	struct Rule
	{
		std::string before;
		std::string after;
		bool breaks;

		std::string create_lookbehind_pattern() const;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // RULE_H
