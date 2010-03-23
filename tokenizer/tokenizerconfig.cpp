#include "tokenizerconfig.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/foreach.hpp>


TokenizerConfig::Cfg TokenizerConfig::fromFile(const std::string &filename)
{
	TokenizerConfig::Cfg p;
	boost::property_tree::ini_parser::read_ini(filename, p);
	return p;
}

TokenizerConfig::Cfg TokenizerConfig::fromStream(std::istream &is)
{
	TokenizerConfig::Cfg p;
	boost::property_tree::ini_parser::read_ini(is, p);
	return p;
}

TokenizerConfig::Cfg& TokenizerConfig::merge(TokenizerConfig::Cfg& accu,
		const TokenizerConfig::Cfg& other)
{
	accu.data() = other.data();
	using boost::property_tree::ptree;
	BOOST_FOREACH (const ptree::value_type& in_other, other) {
		boost::optional< ptree& > in_one;
		if ((in_one = accu.get_child_optional(in_other.first))) {
			merge(*in_one, in_other.second);
		} else {
			accu.push_back(in_other);
		}
	}
	return accu;
}

void TokenizerConfig::write(const Cfg &c, const std::string &filename)
{
	boost::property_tree::ini_parser::write_ini(filename + ".ini", c);
	boost::property_tree::xml_parser::write_xml(filename + ".xml", c);
	boost::property_tree::json_parser::write_json(filename + ".json", c);
}

const TokenizerConfig::Cfg& TokenizerConfig::Default()
{
	static TokenizerConfig::Cfg cfg = TokenizerConfig::fromFile("config.ini");
	return cfg;
}
