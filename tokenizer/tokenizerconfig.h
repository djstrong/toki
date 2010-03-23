#ifndef TOKENIZERCONFIG_H
#define TOKENIZERCONFIG_H

#include <boost/property_tree/ptree.hpp>
#include <set>
#include <unicode/unistr.h>

class TokenizerConfig
{
public:
	typedef boost::property_tree::ptree Cfg;

	static Cfg fromFile(const std::string &filename);

	static Cfg fromStream(std::istream& is);

	static Cfg empty();

	static Cfg& merge(Cfg& accu, const Cfg& other);

	template <typename T>
	static void addUcharsToContainer(const Cfg& cfg, const std::string& key, T& container);

	static void write(const Cfg& c, const std::string& filename);

	static const Cfg& Default();

	Cfg load_default_config(const std::string& id);
};

template <typename T>
void TokenizerConfig::addUcharsToContainer(const Cfg& cfg, const std::string& key, T& container)
{
	std::string prelist = cfg.get<std::string>(key, "");
	UnicodeString pres = UnicodeString::fromUTF8(prelist).unescape();
	for (int i = 0; i < pres.length(); ++i) {
		container.insert(pres.charAt(i));
	}
}


#endif // TOKENIZERCONFIG_H
