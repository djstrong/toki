#ifndef TOKENIZERCONFIG_H
#define TOKENIZERCONFIG_H

#include <boost/property_tree/ptree.hpp>

class TokenizerConfig
{
public:
	typedef boost::property_tree::ptree Cfg;

	static Cfg fromFile(const std::string &filename);

	static Cfg fromStream(std::istream& is);

	static Cfg empty();

	static Cfg& merge(Cfg& accu, const Cfg& other);

	static void write(const Cfg& c, const std::string& filename);

	static const Cfg& Default();

	Cfg load_default_config(const std::string& id);
};

#endif // TOKENIZERCONFIG_H
