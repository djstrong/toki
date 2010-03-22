#include "tokensource.h"
#include "token.h"
#include <ostream>

TokenSource::TokenSource()
{
}

TokenSource::~TokenSource()
{
}

void TokenSource::debug_orths_newline(std::ostream& os)
{
	while (Token* t = getNextToken()) {
		os << t->orth_utf8() << "\n";
		delete t;
	}
}

void TokenSource::debug_tokenize(std::ostream& os)
{
	while (Token* t = getNextToken()) {
		os << t->debugUtf8() << "\n";
		delete t;
	}
	os << "\n";
}
