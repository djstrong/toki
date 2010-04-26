#ifndef LIBTOKI_CONFIG_H
#define LIBTOKI_CONFIG_H

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

	/**
	 * The default_config configuration node
	 */
	const Node& default_config();

	/**
	 * Look for a filename under the search path and return a path to a file
	 * that exists, or an empty string in case of failure
	 */
	std::string find_file_in_search_path(const std::string& filename);

	/**
	 * Open a file stream for a file in the library search path
	 */
	bool open_file_from_search_path(const std::string& filename, std::ifstream& ifs);

	/**
	 * Get a default_config config by name
	 */
	Node get_library_config(const std::string& id);

	std::vector<std::string> get_library_config_path();

	void set_library_config_path(const std::vector<std::string> &);

	void set_library_config_path(const std::string &);

	/**
	 * Convenience class to set the library config path and hev it automatically
	 * reset to the original value upon destruction
	 */
	class LibraryConfigPathSetter
	{
	public:
		/// Constructor
		LibraryConfigPathSetter(const std::string& new_path);

		/// Destructor
		~LibraryConfigPathSetter();
	private:
		/// Stored old path
		std::vector<std::string> old_path_;
	};

	/**
	 * Get the default error stream used by the library to log errors
	 */
	std::ostream* get_default_error_stream();

	/**
	 * Set the default error stream used by the library to log errors.
	 * NULL disables error logging.
	 */
	void set_default_error_stream(std::ostream* os);

} /* end ns Config */ } /* end ns Toki */

#endif // LIBTOKI_CONFIG_H
