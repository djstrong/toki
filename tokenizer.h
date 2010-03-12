#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <istream>

#include "token.h"
#include "unicodesource.h"
#include "icustreamwrapper.h"
#include "icustringsource.h"

class Tokenizer
{
public:
	Tokenizer(UnicodeSource& us);

	Token getNextToken();

	bool hasMoreTokens();

	void debug_tokenize();

private:
	void eatWhitespace();

	UnicodeSource& us_;
	Token::WhitespaceAmount wa_;
};

#endif // TOKENIZER_H
