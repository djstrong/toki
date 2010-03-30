#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <unicode/unistr.h>

namespace Config {

	typedef boost::property_tree::ptree Node;

	Node fromFile(const std::string &filename);

	Node fromStream(std::istream& is);

	Node empty();

	Node merge_copy(const Node& accu, const Node& other);

	Node& merge_into(Node& accu, const Node& other);

	void write(const Node& c, const std::string& filename);

	const Node& Default();

	const Node& get_default_config(const std::string& id);

	std::vector<std::string> get_default_config_search_path();

	void set_default_config_search_path(const std::vector<std::string> &);

	void set_default_config_search_path(const std::string &);

} // end namespace Config

#endif // CONFIG_H
