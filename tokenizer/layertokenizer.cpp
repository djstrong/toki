#include "layertokenizer.h"
#include "token.h"
#include "whitespacetokenizer.h"
#include "tokenlayer.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <unicode/ucnv.h>
#include <unicode/uchar.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "exception.h"

LayerTokenizer::LayerTokenizer(const Config::Node &cfg)
	: Tokenizer(cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(UnicodeSource *input, const Config::Node &cfg)
	: Tokenizer(input, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(boost::shared_ptr<UnicodeSource> input, const Config::Node &cfg)
	: Tokenizer(input, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(std::istream &is, const Config::Node &cfg)
	: Tokenizer(is, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(const UnicodeString &s, const Config::Node &cfg)
	: Tokenizer(s, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::~LayerTokenizer()
{
	for (size_t i = 0; i < layers_.size(); ++i) {
		delete layers_[i];
	}
}

void LayerTokenizer::newInputSource()
{
	input_tokenizer_->setInputSource(input_);
}


void LayerTokenizer::apply_configuration(const Config::Node &cfg)
{
	using boost::property_tree::ptree;
	const ptree& layers_tree = cfg.get_child("layers");

	std::vector<std::string> layer_ids;

	BOOST_FOREACH (const Config::Node::value_type &v, layers_tree) {
		//if (v.first == "layer") {
			layer_ids.push_back(v.second.data());
		//}
	}

	TokenSource* previous = input_tokenizer_.get();
	BOOST_FOREACH (const std::string& id, layer_ids) {
		try {
			std::string layer_class;
			layer_class = cfg.get("layer:" + id + ".class", "");
			TokenLayer* layer;
			try {
				layer = TokenLayer::create(layer_class, previous, cfg.get_child("layer:" + id));
				previous = layer;
				layers_.push_back(layer);
			} catch (TokenLayerFactoryException) {
				std::cerr << "Bad layer class ID " << layer_class
					<< ". Layer with id " << id << " ignored.\n";
			}
		} catch (boost::property_tree::ptree_error& e) {
			std::cerr << "Error while processing configuration for layer with id "
				<< id << ". " << e.what() << "\n";
		}
	}

	if (layers_.empty()) {
		std::cerr << "No valid layers in layer tokenizer!\n";
		throw TokenizerLibError("No valid layers in LayerTokenizer");
	}
}

Token* LayerTokenizer::getNextToken()
{
	return layers_.back()->getNextToken();
}

void LayerTokenizer::reset()
{
	for (size_t i = 0; i < layers_.size(); ++i) {
		layers_[i]->reset();
	}
	input_tokenizer_.reset();
}

