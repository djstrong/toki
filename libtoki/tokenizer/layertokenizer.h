/*
    Copyright (C) 2010 Tomasz Śniatowski, Adam Radziszewski
    Part of the libtoki project

    This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option)
any later version.

    This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. 

    See the LICENSE and COPYING files for more details.
*/

#ifndef LIBTOKI_LAYERTOKENIZER_H
#define LIBTOKI_LAYERTOKENIZER_H

#include <libtoki/tokenizer/tokenizer.h>

#include <boost/scoped_ptr.hpp>

namespace Toki {
	class TokenLayer;

	class WhitespaceTokenizer;

	class LayerTokenizer : public Tokenizer
	{
	public:
		/**
		 * Constructor.
		 *
		 * The configuration is processed for [layer:ID] sections that define
		 * layers and a [layers] section with one or more layer=ID entries that
		 * define which layers to actually use and in what order. Each layer=ID
		 * should have a corresponding [layer:ID] section, but not all [layer:ID]
		 * sections need to be used. The IDs should be unique across a config.
		 *
		 * The subkeys of each [layer:ID] are passed to the appropriate layer's
		 * constructor, the layer class to use being determined by the class subkey.
		 *
		 * The initial tokenization using whitespace characters is confiugurable by
		 * the [input] section, the contents are passed to the WhitespaceTokenizer.
		 * @see WhitespaceTokenizer
		 *
		 * @see Tokenizer::Tokenizer
		 */
		LayerTokenizer(const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given UnicodeSource, and take
		 * ownership
		 * @see Tokenizer::Tokenizer
		 */
		LayerTokenizer(UnicodeSource* input, const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given UnicodeSource as a shared
		 * pointer.
		 * @see Tokenizer::Tokenizer
		 */
		LayerTokenizer(boost::shared_ptr<UnicodeSource> input, const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given std::istream. Note no
		 * ownership is taken and the stream must live long enough.
		 * @see Tokenizer::Tokenizer
		 */
		LayerTokenizer(std::istream& is, const Config::Node& cfg = Config::default_config());

		/**
		 * Constructor shorthand -- start with the given UnicodeString, which is
		 * copied.
		 * @see Tokenizer::Tokenizer
		 */
		LayerTokenizer(const UnicodeString& s, const Config::Node& cfg = Config::default_config());

		/**
		 * Destructor
		 */
		~LayerTokenizer();

		/// TokenSource override
		void new_input_source();

		/// TokenSource override
		void reset();

		/// TokenSource override
		Token* get_next_token();

		/// Output a human-readable synopsis of the loaded layers
		std::string layers_info() const;

		/// Output a long human-readable synopsis of the loaded layers
		std::string layers_long_info(const std::string& sep) const;

		/**
		 * Set the error stream used by teh tokenizer and layers, set to NULL
		 * to disable error logging.
		 */
		void set_error_stream(std::ostream* os);

	private:
		/**
		 * Apply configuraton
		 */
		void apply_configuration(const Config::Node& cfg);

		/// The underlying input token source for the first layer
		boost::scoped_ptr<WhitespaceTokenizer> input_tokenizer_;

		/// The token procesing layers
		std::vector<TokenLayer*> layers_;

		/// error stream object
		std::ostream* error_stream_;
	};

} /* end ns Toki */

#endif // LIBTOKI_LAYERTOKENIZER_H
