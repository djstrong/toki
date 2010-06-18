#include <libtoki/confignode.h>

#ifdef HAVE_CONFIG_D_H
#include <libtoki/config_d.h>
#endif

#include <libtoki/foreach.h>

#include <libtoki/parser/loose_ini_paser.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

#include <libtoki/exception.h>

namespace Toki { namespace Config {

	Node from_file(const std::string &filename)
	{
		Node p;
		try {
			loose_ini_parser::read_loose_ini(filename, p);
		} catch (boost::property_tree::file_parser_error& e) {
			throw TokenizerLibError(e.what());
		}

		return p;
	}

	Node from_stream(std::istream &is)
	{
		Node p;
		try {
			loose_ini_parser::read_loose_ini(is, p);
		} catch (boost::property_tree::file_parser_error& e) {
			throw TokenizerLibError(e.what());
		}
		return p;
	}

	Node& merge_into(Node& accu, const Node& other)
	{
		accu.data() = other.data();
		using boost::property_tree::ptree;
		foreach (const ptree::value_type& in_other, other) {
			boost::optional< ptree& > in_one;
			if ((in_one = accu.get_child_optional(in_other.first))) {
				if (in_other.second.get("_merge", "") == "override") {
					*in_one = in_other.second;
				} else {
					merge_into(*in_one, in_other.second);
				}
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

} /* end ns Config */ } /* end namespace Toki */
