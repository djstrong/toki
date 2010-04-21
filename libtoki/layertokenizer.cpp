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

namespace Toki {

	LayerTokenizer::LayerTokenizer(const Config::Node &cfg)
		: Tokenizer(cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
	{
		apply_configuration(cfg);
		new_input_source();
	}

	LayerTokenizer::LayerTokenizer(UnicodeSource *input, const Config::Node &cfg)
		: Tokenizer(input, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
	{
		apply_configuration(cfg);
		new_input_source();
	}

	LayerTokenizer::LayerTokenizer(boost::shared_ptr<UnicodeSource> input, const Config::Node &cfg)
		: Tokenizer(input, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
	{
		apply_configuration(cfg);
		new_input_source();
	}

	LayerTokenizer::LayerTokenizer(std::istream &is, const Config::Node &cfg)
		: Tokenizer(is, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
	{
		apply_configuration(cfg);
		new_input_source();
	}

	LayerTokenizer::LayerTokenizer(const UnicodeString &s, const Config::Node &cfg)
		: Tokenizer(s, cfg), input_tokenizer_(new WhitespaceTokenizer(cfg.get_child("input", Config::Node())))
	{
		apply_configuration(cfg);
		new_input_source();
	}

	LayerTokenizer::~LayerTokenizer()
	{
		for (size_t i = 0; i < layers_.size(); ++i) {
			delete layers_[i];
		}
	}

	std::string LayerTokenizer::layers_info() const
	{
		std::stringstream ss;
		ss << "LTok:" << layers_.size() << ": ";
		for (size_t i = 0; i < layers_.size(); ++i) {
			ss << layers_[i]->info() << " ";
		}
		return ss.str();
	}

	std::string LayerTokenizer::layers_long_info(const std::string &sep) const
	{
		std::stringstream ss;
		for (size_t i = 0; i < layers_.size(); ++i) {
			ss << layers_[i]->long_info() << sep;
		}
		return ss.str();
	}

	void LayerTokenizer::new_input_source()
	{
		input_tokenizer_->set_input_source(get_input_source());
	}


	void LayerTokenizer::apply_configuration(const Config::Node &cfg)
	{
		using boost::property_tree::ptree;

		const ptree* ltp = NULL;
		try {
			ltp = &cfg.get_child("layers");
		} catch (boost::property_tree::ptree_error& e) {
			throw TokenizerLibError("No layers in LayerTokenizer configuration");
		}
		const ptree& layers_tree = *ltp;

		std::vector<std::string> layer_ids;

		BOOST_FOREACH (const Config::Node::value_type &v, layers_tree) {
			if (v.first == "layer") {
				layer_ids.push_back(v.second.data());
			}
		}

		TokenSource* previous = input_tokenizer_.get();
		BOOST_FOREACH (const std::string& id, layer_ids) {
			try {
				std::string layer_class;
				layer_class = cfg.get("layer:" + id + ".class", "");
				TokenLayer* layer;
				try {
					Config::Node layer_cfg = cfg.get_child("layer:" + id);
					layer_cfg.put("id", id);
					layer = TokenLayer::create(layer_class, previous, layer_cfg);
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

	Token* LayerTokenizer::get_next_token()
	{
		return layers_.back()->get_next_token();
	}

	void LayerTokenizer::reset()
	{
		for (size_t i = 0; i < layers_.size(); ++i) {
			layers_[i]->reset();
		}
		input_tokenizer_->reset();
	}

} /* end namespace Toki */
