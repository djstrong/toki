#include "token.h"
#include <sstream>

Token::Token(const UnicodeString& orth, const std::string& type, WhitespaceAmount wa_before)
		: orth_(orth)
		, type_(type)
		, preceeding_whitespace_(wa_before)
{
}

Token::Token(const char* orth_utf8, const std::string& type, WhitespaceAmount wa_before)
		: orth_(UnicodeString::fromUTF8(orth_utf8))
		, type_(type)
		, preceeding_whitespace_(wa_before)
{
}

std::string Token::orth_utf8() const
{
	std::string result;
	orth_.toUTF8String(result);
	return result;
}

std::string Token::debugUtf8() const
{
	std::stringstream ss;
	ss << "[" << orth_utf8() << "]-" << type_ << "-" << preceeding_whitespace_ << "-";
	return ss.str();
}
