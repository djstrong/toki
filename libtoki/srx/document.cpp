#include "document.h"
#include <libxml++/libxml++.h>
#include <libxml++/nodes/node.h>
#include <libxml++/nodes/element.h>
#include <boost/foreach.hpp>


namespace {
	const xmlpp::Node* get_child_or_null(const xmlpp::Node* n, const char* name)
	{
		const xmlpp::Node::NodeList list = n->get_children(name);
		if (list.empty()) return NULL;
		return list.front();
	}

	const xmlpp::Node* get_child_or_throw(const xmlpp::Node* n, const char* name)
	{
		const xmlpp::Node* c = get_child_or_null(n, name);
		if (!c) {
			std::stringstream ss;
			ss << "no " << "<" << name << ">";
			throw Toki::Srx::ParseError(ss.str());
		}
		return c;
	}
	
	std::string get_child_text_or_empty(const xmlpp::Node* n, const char* name)
	{
		const xmlpp::Element* el = dynamic_cast<const xmlpp::Element*>(
			get_child_or_null(n, name));
		if (el) {
			const xmlpp::TextNode* t = el->get_child_text();
			if (t) return t->get_content();
		}
		return "";
	}
} /* end anon ns */

namespace Toki { namespace Srx {

	Document::Document()
	{
	}

	void Document::load(std::istream &is)
	{
		xmlpp::DomParser dom;
		dom.set_substitute_entities();
		dom.parse_stream(is);
		if (dom) {
			const xmlpp::Node* root = dom.get_document()->get_root_node();
			if (!root) throw ParseError("no root");
			if (root->get_name() != "srx") throw ParseError("root node not <srx>");
			const xmlpp::Node* header = get_child_or_null(root, "header");
			if (header) {
				process_header_node(header);
			}
			const xmlpp::Node* body = get_child_or_throw(root, "body");
			const xmlpp::Node* languagerules = get_child_or_throw(body, "languagerules");
			const xmlpp::Node::NodeList lrl = languagerules->get_children("languagerule");
			if (lrl.empty()) throw ParseError("no <languagerule>");
			BOOST_FOREACH (const xmlpp::Node* n, lrl) {
				process_languagerule_node(n);
			}
			const xmlpp::Node* maprules = get_child_or_throw(body, "maprules");
			const xmlpp::Node::NodeList mrl = maprules->get_children("languagemap");
			if (mrl.empty()) throw ParseError("no <languagemap>");
			BOOST_FOREACH (const xmlpp::Node* n, mrl) {
				process_languagemap_node(n);
			}

		} else {
			throw ParseError("Parse error");
		}
	}

	void Document::process_header_node(const xmlpp::Node */*n*/)
	{
		//no action yet
	}

	void Document::process_languagerule_node(const xmlpp::Node *n)
	{
		const xmlpp::Element* el = dynamic_cast<const xmlpp::Element*>(n);
		if (!el) throw ParseError("<languagerule> not an Element");
		std::string name = el->get_attribute_value("languagerulename");
		if (name.empty()) throw ParseError("<languagerule> with empty languagerulename attribute");
		const xmlpp::Node::NodeList lr = n->get_children("rule");
		BOOST_FOREACH (const xmlpp::Node* n, lr) {
			process_rule_node(name, n);
		}
	}

	void Document::process_rule_node(const std::string &language, const xmlpp::Node *n)
	{
		const xmlpp::Element* el = dynamic_cast<const xmlpp::Element*>(n);
		if (!el) throw ParseError("<rule> not an Element");
		Rule rule;
		std::string break_attr = el->get_attribute_value("break");
		if (break_attr.empty() || break_attr == "yes") {
			rule.breaks = true;
		} else if (break_attr == "no") {
			rule.breaks = false;
		} else {
			throw ParseError("<rule> with invalid break attribute");
		}
		rule.before = get_child_text_or_empty(n, "beforebreak");
		rule.after = get_child_text_or_empty(n, "afterbreak");
		if (rule.before.empty() && rule.after.empty()) {
			throw ParseError("<rule> with empty <beforebreak> and <afterbreak>");
		}
		language_rules_[language].push_back(rule);
	}

	void Document::process_languagemap_node(const xmlpp::Node */*n*/)
	{
		//TODO
	}

	std::vector<Rule> Document::get_all_rules() const
	{
		std::vector<Rule> v;
		language_rules_t::const_iterator li = language_rules_.begin();
		for (; li != language_rules_.end(); ++li) {
			std::vector<Rule>::const_iterator i = li->second.begin();
			for (; i != li->second.end(); ++i) {
				v.push_back(*i);
			}
		}
		return v;
	}

	std::vector<Rule> Document::get_rules_for_lang(const std::string &/*lang*/) const
	{
		// TODO make it real
		return get_all_rules();
	}

	std::string Document::info() const
	{
		std::stringstream ss;
		ss << "SRX " << language_rules_.size() << " languages with ";
		language_rules_t::const_iterator li = language_rules_.begin();
		for (; li != language_rules_.end(); ++li) {
			ss << li->second.size() << " ";
		}
		ss << "rules";
		return ss.str();
	}

} /* end ns Srx */ } /* end ns Toki */
