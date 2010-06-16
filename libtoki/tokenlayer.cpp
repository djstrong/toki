#include <libtoki/foreach.h>
#include <libtoki/tokenlayer.h>
#include <libtoki/token_layers/inittokenlayers.h>
#include <libtoki/token.h>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

namespace Toki {

	TokenLayer::TokenLayer(TokenSource* input, const Config::Node& props)
		: input_(input), process_token_types_(), do_not_process_token_types_(),
		id_(), error_stream_(NULL)
	{
		std::vector<std::string> sv;
		std::string data = props.get("process_types", "");
		boost::algorithm::split(sv, data, std::bind1st(std::equal_to<char>(), ' '));
		foreach (const std::string& s, sv) {
			if (!s.empty()) {
				process_token_types_.insert(s);
			}
		}
		std::vector<std::string> sv2;
		std::string data2 = props.get("ignore_types", "");
		boost::algorithm::split(sv2, data2, std::bind1st(std::equal_to<char>(), ' '));
		foreach (const std::string& s2, sv2) {
			if (!s2.empty()) {
				do_not_process_token_types_.insert(s2);
			}
		}
		id_ = props.get("id", "?");
	}

	TokenLayer::~TokenLayer()
	{
	}

	void TokenLayer::reset()
	{
	}

	std::string TokenLayer::info() const
	{
		return "tokenlayer";
	}

	std::string TokenLayer::long_info() const
	{
		return "Layer '" + id_ + "'";
	}

	TokenLayer* TokenLayer::create(std::string class_id, TokenSource* input, const Config::Node& props)
	{
		return TokenLayerFactory::Instance().CreateObject(class_id, input, props);
	}

	std::vector<std::string> TokenLayer::available_layer_types()
	{
		return TokenLayerFactory::Instance().RegisteredIds();
	}

	Token* TokenLayer::get_token_from_input()
	{
		return input_->get_next_token();
	}

	Token* TokenLayer::get_next_token()
	{
		Token* t = get_token_from_input();
		if (t) {
			if (should_process_token_type(t->type())) {
				t =  process_token(t);
			}
		}
		return t;
	}

	Token* TokenLayer::process_token(Token *t)
	{
		return t;
	}

	bool TokenLayer::should_process_token_type(const std::string &t)
	{
		if (do_not_process_token_types_.find(t) != do_not_process_token_types_.end()) {
			return false;
		} else {
			if (process_token_types_.empty()) {
				return true;
			} else {
				return process_token_types_.find(t) != process_token_types_.end();
			}
		}
	}

	void TokenLayer::set_error_stream(std::ostream *os)
	{
		error_stream_ = os;
	}

	static bool registered = init_token_layers();

} /* end namespace Toki */
