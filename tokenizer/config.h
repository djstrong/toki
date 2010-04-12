#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <unicode/unistr.h>

namespace Toki { namespace Config {

	/**
	 * Typedef for the configuration type passed around
	 */
	typedef boost::property_tree::ptree Node;

	/**
	 * Load configuration from a file (may throw)
	 */
	Node fromFile(const std::string &filename);

	/**
	 * Load configuration from a file (may throw)
	 */
	Node fromStream(std::istream& is);

	/**
	 * Merge two config nodes and return a node with the merged contents
	 */
	Node merge_copy(const Node& accu, const Node& other);

	/**
	 * Merge a config node into another.
	 */
	Node& merge_into(Node& accu, const Node& other);

	/**
	 * Write a config node into a file
	 */
	void write(const Node& c, const std::string& filename);

	/**
	 * The default configuration node
	 */
	const Node& Default();

	/**
	 * Get a default config by name
	 */
	Node get_library_config(const std::string& id);

	std::vector<std::string> get_library_config_path();

	void set_library_config_path(const std::vector<std::string> &);

	void set_library_config_path(const std::string &);

} /* end ns Config */ } /* end ns Toki */

#endif // CONFIG_H
