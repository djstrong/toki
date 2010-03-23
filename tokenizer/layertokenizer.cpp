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

LayerTokenizer::LayerTokenizer(const TokenizerConfig::Cfg& cfg)
	: Tokenizer(cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", TokenizerConfig::Cfg())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(UnicodeSource *input, const TokenizerConfig::Cfg &cfg)
	: Tokenizer(input, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", TokenizerConfig::Cfg())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(boost::shared_ptr<UnicodeSource> input, const TokenizerConfig::Cfg &cfg)
	: Tokenizer(input, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", TokenizerConfig::Cfg())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(std::istream &is, const TokenizerConfig::Cfg &cfg)
	: Tokenizer(is, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", TokenizerConfig::Cfg())))
{
	apply_configuration(cfg);
	newInputSource();
}

LayerTokenizer::LayerTokenizer(const UnicodeString &s, const TokenizerConfig::Cfg &cfg)
	: Tokenizer(s, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", TokenizerConfig::Cfg())))
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


void LayerTokenizer::apply_configuration(const TokenizerConfig::Cfg &cfg)
{
	//init_token_layers();

	using boost::property_tree::ptree;
	const ptree& layers_tree = cfg.get_child("layers");

	std::vector<std::string> layer_ids;

	BOOST_FOREACH (const ptree::value_type &v, layers_tree) {
		//if (v.first == "layer") {
			layer_ids.push_back(v.second.data());
		//}
	}

	TokenSource* previous = input_tokenizer_.get();
	BOOST_FOREACH (const std::string& id, layer_ids) {
		std::string layer_class = cfg.get("layer_" + id + ".class", "");
		TokenLayer* layer;
		try {
			layer = TokenLayer::create(layer_class, previous, cfg.get_child("layer_" + id));
			previous = layer;
			layers_.push_back(layer);
		} catch (TokenLayerFactoryException) {
			std::cerr << "Bad layer class ID " << layer_class
				<< ". Layer with id " << id << " ignored.\n";
		}
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

