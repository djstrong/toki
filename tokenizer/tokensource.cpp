#include "tokensource.h"
#include "token.h"
#include <ostream>
#include <sstream>

TokenSource::TokenSource()
{
}

TokenSource::~TokenSource()
{
}

void TokenSource::tokenize(boost::function<void(Token *)> sink)
{
	while (Token* t = getNextToken()) {
		sink(t);
	}
}

void TokenSource::debug_orths_newline(std::ostream& os)
{
	while (Token* t = getNextToken()) {
		os << t->orth_utf8() << "\n";
		delete t;
	}
}

std::string TokenSource::debug_orths_newline()
{
	std::stringstream ss;
	debug_orths_newline(ss);
	return ss.str();
}

void TokenSource::debug_tokenize(std::ostream& os)
{
	while (Token* t = getNextToken()) {
		os << t->debugUtf8() << "\n";
		delete t;
	}
}

std::string TokenSource::debug_tokenize()
{
	std::stringstream ss;
	debug_tokenize(ss);
	return ss.str();
}
