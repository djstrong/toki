#ifndef LIBTOKI_SRX_DOCUMENT_H
#define LIBTOKI_SRX_DOCUMENT_H

#include <string>
#include <map>
#include <vector>
#include <istream>

#include "exception.h"
#include "rule.h"

// forward decl
namespace xmlpp {
	class Node;
}

namespace Toki { namespace Srx {

	class ParseError : public Error
	{
	public:
		ParseError(const std::string& what)
			: Error("Parse error: " + what)
		{
		}

		~ParseError() throw()
		{
		}
	};

	class Document {
	public:
		Document();

		void load(std::istream &is);

		/**
		 * Get all the rules in the document, regardless of language
		 */
		std::vector<Rule> get_all_rules() const;

		/**
		 * Get the rules for a given language code
		 * TODO make it work
		 */
		std::vector<Rule> get_rules_for_lang(const std::string& lang) const;

		/**
		 * Get a human-readable summary about the loaded SRX
		 */
		std::string info() const;

	private:
		void process_header_node(const xmlpp::Node* n);
		void process_languagerule_node(const xmlpp::Node* n);
		void process_rule_node(const std::string& language, const xmlpp::Node* n);
		void process_languagemap_node(const xmlpp::Node* n);

		typedef std::map<std::string, std::vector<Rule> > language_rules_t;
		language_rules_t language_rules_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_DOCUMENT_H
