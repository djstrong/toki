#include "tokenizerconfig.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/foreach.hpp>

TokenizerConfig::TokenizerConfig(const std::string &filename)
{
	boost::property_tree::ini_parser::read_ini(filename, props_);
}

TokenizerConfig::TokenizerConfig(std::istream &is)
{
	boost::property_tree::ini_parser::read_ini(is, props_);
}

TokenizerConfig& TokenizerConfig::append(const TokenizerConfig &other)
{
	typedef const boost::property_tree::ptree::value_type& iter_t;
	typedef boost::optional< boost::property_tree::ptree & > maybe_ptree;

	BOOST_FOREACH (iter_t outer, other.props()) {
		maybe_ptree child;
		if ((child = props_.get_child_optional(outer.first))) {
			BOOST_FOREACH (iter_t inner, *child) {
				maybe_ptree inner_child;
				if ((inner_child = child->get_child_optional(inner.first))) {
					inner_child->data() = inner.second.data();
				} else {
					inner_child->push_back(inner);
				}
			}
		} else {
			props_.push_back(outer);
		}
	}

	return *this;
}
