#ifndef LIBTOKI_SRX_H
#define LIBTOKI_SRX_H

#include <string>
#include <map>
#include <vector>
#include <istream>

namespace Toki { namespace Srx {

	struct Rule
	{
		std::string before;
		std::string after;
		bool breaks;
	};

	class SrxDocument {
	public:
		SrxDocument();
		void load(std::istream &is);

	private:
		std::map<std::string, std::vector<Rule> > language_rules_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif
