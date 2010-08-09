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

#include <libtoki/token.h>
#include <libtoki/tokenizer/tokenizer.h>
#include <libtoki/unicode/nullsource.h>
#include <libtoki/unicode/icustringwrapper.h>
#include <libtoki/unicode/istreamwrapper.h>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <ostream>

namespace Toki {

	Tokenizer::Tokenizer(const Config::Node& cfg)
		: TokenSource(), input_()
	{
		set_null_input_source();
		apply_configuration(cfg);
	}

	Tokenizer::Tokenizer(UnicodeSource *input, const Config::Node& cfg)
		: TokenSource(), input_()
	{
		set_input_source(input);
		apply_configuration(cfg);
	}

	Tokenizer::Tokenizer(boost::shared_ptr<UnicodeSource> input, const Config::Node &cfg)
		: TokenSource(), input_()
	{
		set_input_source(input);
		apply_configuration(cfg);
	}

	Tokenizer::Tokenizer(std::istream &is, const Config::Node &cfg)
		: TokenSource(), input_()
	{
		set_input_source(is, cfg.get<int>("input_buffer_size", 200));
		apply_configuration(cfg);
	}

	Tokenizer::Tokenizer(const UnicodeString &s, const Config::Node &cfg)
		: TokenSource(), input_()
	{
		set_input_source(s);
		apply_configuration(cfg);
	}

	Tokenizer::~Tokenizer()
	{
	}

	void Tokenizer::set_null_input_source()
	{
		set_input_source(new NullUnicodeSource());
	}

	void Tokenizer::set_input_source(UnicodeSource *us)
	{
		input_.reset(us);
		new_input_source();
	}

	void Tokenizer::set_input_source(boost::shared_ptr<UnicodeSource> us)
	{
		input_ = us;
		new_input_source();
	}

	void Tokenizer::set_input_source(std::istream &is, int bufsize)
	{
		set_input_source(new UnicodeIstreamWrapper(is, bufsize));
	}

	void Tokenizer::set_input_source(const UnicodeString &s)
	{
		set_input_source(new UnicodeIcuStringWrapper(s));
	}

	void Tokenizer::reset()
	{
	}

	void Tokenizer::apply_configuration(const Config::Node &/*cfg*/)
	{
	}

} /* end namespace Toki */
