#include "whitespacetokenizer.h"
#include "tokenizer.h"

#include <unicode/ucnv.h>
#include <unicode/uchar.h>
#include <iostream>

WhitespaceTokenizer::WhitespaceTokenizer(const TokenizerConfig::Cfg &cfg)
	: Tokenizer(cfg), wa_(Token::WA_None), token_type_()
{
	token_type_ = cfg.get("token_type", "t");
}

WhitespaceTokenizer::WhitespaceTokenizer(UnicodeSource* us, const TokenizerConfig::Cfg& cfg)
	: Tokenizer(us, cfg), wa_(Token::WA_None)
{
	token_type_ = cfg.get("token_type", "t");
	eatWhitespace();
}

void WhitespaceTokenizer::reset()
{
	wa_ = Token::WA_None;
}

void WhitespaceTokenizer::newInputSource()
{
	eatWhitespace();
}


void WhitespaceTokenizer::eatWhitespace()
{
	int ws = 0; int nl = 0;
	while (input().hasMoreChars()) {
		UChar u = input_->peekNextChar();
		if (!u_isUWhiteSpace(u)) {
			break;
		} else {
			ws++;
			if (u == 0xA) {
				nl++;
			}
			input().getNextChar();
		}
	}
	if (nl > 1) {
		wa_ = Token::WA_ManyNewlines;
	} else if (nl == 1) {
		wa_ = Token::WA_Newline;
	} else if (ws > 1) {
		wa_ = Token::WA_ManySpaces;
	} else if (ws == 1) {
		wa_ = Token::WA_Space;
	} else {
		wa_ = Token::WA_None;
	}
}

Token* WhitespaceTokenizer::getNextToken()
{
	if (!input().hasMoreChars()) {
		return NULL;
	}
	UnicodeString orth;
	UChar u = input().getNextChar();
	orth = u;
	while (input().hasMoreChars()) {
		u = input().peekNextChar();
		if (u_isUWhiteSpace(u)) {
			break;
		} else {
			orth += u;
			input().getNextChar();
		}
	}
	Token* t  = new Token(orth, token_type_, wa_);
	eatWhitespace();
	return t;
}
