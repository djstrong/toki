#include "tokenizer.h"
#include "token.h"
#include "nullunicodesource.h"

#include "unicodeicustringwrapper.h"
#include "unicodeistreamwrapper.h"

#include <ostream>

Tokenizer::Tokenizer(const TokenizerConfig::Cfg& /*cfg*/)
	: TokenSource(), input_()
{
	setNullInputSource();
}

Tokenizer::Tokenizer(UnicodeSource *input, const TokenizerConfig::Cfg& /*cfg*/)
	: TokenSource(), input_()
{
	setInputSource(input);
}

Tokenizer::Tokenizer(boost::shared_ptr<UnicodeSource> input, const TokenizerConfig::Cfg &/*cfg*/)
	: TokenSource(), input_()
{
	setInputSource(input);
}

Tokenizer::Tokenizer(std::istream &is, const TokenizerConfig::Cfg &cfg)
	: TokenSource(), input_()
{
	setInputSource(is, cfg.get<int>("input_buffer_size", 200));
}

Tokenizer::Tokenizer(const UnicodeString &s, const TokenizerConfig::Cfg &/*cfg*/)
	: TokenSource(), input_()
{
	setInputSource(s);
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
