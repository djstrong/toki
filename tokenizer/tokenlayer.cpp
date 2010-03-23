#include "tokenlayer.h"
#include "token_layers/inittokenlayers.h"
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

TokenLayer::TokenLayer(TokenSource* input, const Properties& props)
	: input_(input), process_token_types_(), do_not_process_token_types_()
{
	std::vector<std::string> sv;
	std::string data = props.get("process_types", "");
	boost::algorithm::split(sv, data, std::bind1st(std::equal_to<char>(), ','));
	BOOST_FOREACH (const std::string& s, sv) {
		if (!s.empty()) {
			process_token_types_.insert(s);
		}
	}
	std::vector<std::string> sv2;
	std::string data2 = props.get("do_not_process_types", "");
	boost::algorithm::split(sv2, data2, std::bind1st(std::equal_to<char>(), ','));
	BOOST_FOREACH (const std::string& s2, sv2) {
		if (!s2.empty()) {
			do_not_process_token_types_.insert(s2);
		}
	}
}

TokenLayer::~TokenLayer()
{
}

void TokenLayer::reset()
{
}

TokenLayer* TokenLayer::create(std::string class_id, TokenSource* input, const Properties& props)
{
	return TokenLayerFactory::Instance().CreateObject(class_id, input, props);
}

Token* TokenLayer::getTokenFromInput()
{
	return input_->getNextToken();
}

bool TokenLayer::shouldProcessTokenType(const std::string &t)
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

static bool registered = init_token_layers();
