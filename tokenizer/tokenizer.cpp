#include "tokenizer.h"
#include "token.h"
#include "nullunicodesource.h"

#include "unicodeicustringwrapper.h"
#include "unicodeistreamwrapper.h"

#include <ostream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

Tokenizer::Tokenizer(const TokenizerConfig::Cfg& cfg)
	: TokenSource(), input_()
{
	setNullInputSource();
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(UnicodeSource *input, const TokenizerConfig::Cfg& cfg)
	: TokenSource(), input_()
{
	setInputSource(input);
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(boost::shared_ptr<UnicodeSource> input, const TokenizerConfig::Cfg &cfg)
	: TokenSource(), input_()
{
	setInputSource(input);
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(std::istream &is, const TokenizerConfig::Cfg &cfg)
	: TokenSource(), input_()
{
	setInputSource(is, cfg.get<int>("input_buffer_size", 200));
	apply_configuration(cfg);
}

Tokenizer::Tokenizer(const UnicodeString &s, const TokenizerConfig::Cfg &cfg)
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

void Tokenizer::apply_configuration(const TokenizerConfig::Cfg &cfg)
{
	std::string a = cfg.get<std::string>("debug.format", "[$orth]-$type-$wa_n\n");
	debug_format_ = "";
	UnicodeString::fromUTF8(a).unescape().toUTF8String(debug_format_);
}

std::string Tokenizer::debug_formatted(const std::string& format)
{
	std::stringstream ss;
	while (Token* t = getNextToken()) {
		std::string out = format;
		boost::replace_first(out, "$orth", t->orth_utf8());
		boost::replace_first(out, "$type", t->type());
		boost::replace_first(out, "$wa_n",
		boost::lexical_cast<std::string>(t->preceeding_whitespace()));
		ss << out;
		delete t;
	}
	return ss.str();
}

std::string Tokenizer::debug_formatted()
{
	return debug_formatted(debug_format_);
}
