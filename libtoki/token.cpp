#include "token.h"
#include <sstream>

namespace Toki {

	std::string Token::WA_as_string(WhitespaceAmount wa)
	{
		switch (wa) {
		case Token::WA_None:
			return "none";
		case Token::WA_Space:
			return "space";
		case Token::WA_ManySpaces:
			return "spaces";
		case Token::WA_Newline:
			return "newline";
		case Token::WA_ManyNewlines:
			return "newlines";
		default:
			return "???";
		}
	}

	Token::Token(const UnicodeString& orth, const std::string& type, WhitespaceAmount wa_before)
			: orth_(orth)
			, type_(type)
			, preceeding_whitespace_(wa_before)
	{
#ifdef LIBTOKI_TRACK_TOKEN_CREATION
		++instance_count_;
#endif
	}

	Token::Token(const char* orth_utf8, const std::string& type, WhitespaceAmount wa_before)
			: orth_(UnicodeString::fromUTF8(orth_utf8))
			, type_(type)
			, preceeding_whitespace_(wa_before)
	{
#ifdef LIBTOKI_TRACK_TOKEN_CREATION
		++instance_count_;
#endif
	}

#ifdef LIBTOKI_TRACK_TOKEN_CREATION
	Token::Token(const Token& other)
		: orth_(other.orth_), type_(other_.type_),
		preceeding_whitespace_(other.preceeding_whitespace_)
	{
		++instance_count_;
	}

	Token::~Token()
	{
		--instance_count_;
	}
#endif

	std::string Token::orth_utf8() const
	{
		std::string result;
		orth_.toUTF8String(result);
		return result;
	}

} /* end namespace Toki */
