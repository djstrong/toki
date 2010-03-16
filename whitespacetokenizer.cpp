#include "whitespacetokenizer.h"
#include "tokenizer.h"

#include <unicode/ucnv.h>
#include <unicode/uchar.h>
#include <iostream>

WhitespaceTokenizer::WhitespaceTokenizer(UnicodeSource& us)
	: us_(us), wa_(Token::WA_None)
{
	eatWhitespace();
}

void WhitespaceTokenizer::eatWhitespace()
{
	int ws = 0; int nl = 0;
	while (us_.hasMoreChars()) {
		UChar u = us_.peekNextChar();
		if (!u_isUWhiteSpace(u)) {
			break;
		} else {
			ws++;
			if (u == 0xA) {
				nl++;
			}
			us_.getNextChar();
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
	UnicodeString orth;

	UChar u = us_.getNextChar();
	orth = u;
	while (us_.hasMoreChars()) {
		u = us_.peekNextChar();
		if (u_isUWhiteSpace(u)) {
			break;
		} else {
			orth += u;
			us_.getNextChar();
		}
	}
	Token* t  = new Token(orth, "t", wa_);
	eatWhitespace();
	return t;
}
