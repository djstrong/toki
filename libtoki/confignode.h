#ifndef LIBTOKI_CONFIGNODE_H
#define LIBTOKI_CONFIGNODE_H

#include <map>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <unicode/unistr.h>
#include <ostream>

namespace Toki { namespace Config {

	/**
	 * Typedef for the configuration type passed around
	 */
	typedef boost::property_tree::ptree Node;

	/**
	 * Load configuration from a file (may throw)
	 */
	Node from_file(const std::string &filename);

	/**
	 * Load configuration from a file (may throw)
	 */
	Node from_stream(std::istream& is);

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

} /* end ns Config */ } /* end ns Toki */

#endif // LIBTOKI_CONFIGNODE_H
