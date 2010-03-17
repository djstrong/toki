#include "tokenizer.h"
#include "token.h"
#include "whitespacetokenizer.h"

#include <claw/configuration_file.hpp>
#include <libxml++/libxml++.h>

#include <unicode/ucnv.h>
#include <unicode/uchar.h>

#include <fstream>
#include <iostream>
#include <sstream>

Tokenizer::Tokenizer(UnicodeSource& us)
		: us_(us), source_(NULL)
{
	source_ = new WhitespaceTokenizer(us_);
}

Tokenizer::~Tokenizer()
{
	for (size_t i = 0; i < layers_.size(); ++i) {
		delete layers_[i];
	}
	delete source_;
}

void Tokenizer::parse_configuration_file(const std::string &fn)
{
	std::ifstream ifs(fn.c_str());
	parse_configuration(ifs);
}

void Tokenizer::parse_configuration(std::istream& s)
{
	claw::configuration_file cfg(s);
	claw::configuration_file::const_field_iterator i =
		cfg.field_begin("layers", "layer");
	claw::configuration_file::const_field_iterator end =
		cfg.field_end("layers", "layer");
	std::vector<std::string> layer_names;
	TokenSource* previous = source_;
	while (i != end) {
		layer_names.push_back(*i);
		std::string layer_class = cfg("layer_" + *i, "class");
		TokenLayer* layer;
		try {
			layer = TokenLayer::create(layer_class, previous);
			previous = layer;
			layers_.push_back(layer);
		} catch (TokenLayerFactoryException) {
			std::cerr << "Bad layer class ID " << layer_class
				<< ". Layer with id " << *i << " ignored.\n";
		}
		i++;
	}

}

void Tokenizer::parse_configuration(const std::string& s)
{
	std::stringstream ss;
	ss << s;
	parse_configuration(ss);
}

Token* Tokenizer::getNextToken()
{
	return layers_.back()->getNextToken();
}

void Tokenizer::reset()
{
	for (size_t i = 0; i < layers_.size(); ++i) {
		layers_[i]->reset();
	}
}

void Tokenizer::debug_tokenize()
{
	while (Token* t = getNextToken()) {
		std::cout << t->debugUtf8();
		delete t;
	}
	std::cout << "\n";
}
