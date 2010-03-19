#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <istream>
#include <vector>

#include "tokenlayer.h"
#include "unicodesource.h"
#include "tokensource.h"
#include "unicodeistreamwrapper.h"
#include "unicodeicustringwrapper.h"

class Tokenizer : public TokenSource
{
public:
	Tokenizer(UnicodeSource& us);

	//DRAFT: Tokenizer(const TokenizerConfig& cfg = TokenizerConfig::Default());

	~Tokenizer();

	void parse_configuration_file(const std::string& fn);

	void parse_configuration(std::istream& is);

	void parse_configuration(const std::string& s);

	Token* getNextToken();

	void reset();

	void debug_tokenize();

private:
	void eatWhitespace();

	UnicodeSource& us_;

	TokenSource* source_;

	std::vector<TokenLayer*> layers_;
};

#endif // TOKENIZER_H
