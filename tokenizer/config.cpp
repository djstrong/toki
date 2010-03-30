#include "config.h"

#include "parser/loose_ini_paser.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/foreach.hpp>

#include <iostream>

#include "exception.h"

namespace Config {

Node fromFile(const std::string &filename)
{
	Node p;
	try {
		loose_ini_parser::read_loose_ini(filename, p);
	} catch (boost::property_tree::file_parser_error& e) {
		throw TokenizerLibError(e.what());
	}

	return p;
}

Node fromStream(std::istream &is)
{
	Node p;
	try {
		boost::property_tree::ini_parser::read_ini(is, p);
	} catch (boost::property_tree::file_parser_error& e) {
		throw TokenizerLibError(e.what());
	}
	return p;
}

Node& merge_into(Node& accu, const Node& other)
{
	accu.data() = other.data();
	using boost::property_tree::ptree;
	BOOST_FOREACH (const ptree::value_type& in_other, other) {
		boost::optional< ptree& > in_one;
		if ((in_one = accu.get_child_optional(in_other.first))) {
			merge_into(*in_one, in_other.second);
		} else {
			accu.push_back(in_other);
		}
	}
	return accu;
}

Node merge_copy(const Node &one, const Node &other)
{
	Node accu(one);
	merge_into(accu, other);
	return accu;
}

void write(const Node &c, const std::string &filename)
{
	int errors = 0;
	try {
		boost::property_tree::ini_parser::write_ini(filename + ".ini", c);
	} catch (boost::property_tree::file_parser_error& e) {
		errors++;
	}
	try {
		boost::property_tree::xml_parser::write_xml(filename + ".xml", c);
	} catch (boost::property_tree::file_parser_error& e) {
		errors++;
	}
	try {
		boost::property_tree::json_parser::write_json(filename + ".json", c);
	} catch (boost::property_tree::file_parser_error& e) {
		errors++;
	}
	if (errors > 0) {
		std::cerr << "Config write failed!\n";
	}
}

const Node& Default()
{
	bool initialized = false;
	static Node cfg;
	if (!initialized) {
		try {
			cfg = fromFile("config.ini");
		} catch (TokenizerLibError& e) {
			throw TokenizerLibError(std::string("Default config error! ") + e.what());
		}
		initialized = true;
	}
	return cfg;
}

} //end namespace Config

