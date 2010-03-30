#include "tokenizer.h"
#include "token.h"
#include "nullunicodesource.h"

#include "unicodeicustringwrapper.h"
#include "unicodeistreamwrapper.h"

#include <ostream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

Tokenizer::Tokenizer(const Config::Node& cfg)
	: TokenSource(), input_()
{
	setNullInputSource();
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(UnicodeSource *input, const Config::Node& cfg)
	: TokenSource(), input_()
{
	setInputSource(input);
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(boost::shared_ptr<UnicodeSource> input, const Config::Node &cfg)
	: TokenSource(), input_()
{
	setInputSource(input);
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(std::istream &is, const Config::Node &cfg)
	: TokenSource(), input_()
{
	setInputSource(is, cfg.get<int>("input_buffer_size", 200));
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(const UnicodeString &s, const Config::Node &cfg)
	: TokenSource(), input_()
{
	setInputSource(s);
	apply_configuration(cfg);
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::setNullInputSource()
{
	setInputSource(new NullUnicodeSource());
}

void Tokenizer::setInputSource(UnicodeSource *us)
{
	input_.reset(us);
	newInputSource();
}

void Tokenizer::setInputSource(boost::shared_ptr<UnicodeSource> us)
{
	input_ = us;
	newInputSource();
}

void Tokenizer::setInputSource(std::istream &is, int bufsize)
{
	setInputSource(new UnicodeIstreamWrapper(is, bufsize));
}

void Tokenizer::setInputSource(const UnicodeString &s)
{
	setInputSource(new UnicodeIcuStringWrapper(s));
}

void Tokenizer::reset()
{
}

void Tokenizer::apply_configuration(const Config::Node &/*cfg*/)
{
}
