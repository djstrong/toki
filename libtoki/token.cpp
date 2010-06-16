#include <libtoki/token.h>
#include <sstream>

namespace Toki {



	Token::Token(const UnicodeString& orth, const std::string& type, Whitespace::Enum wa_before)
			: orth_(orth)
			, type_(type)
			, preceeding_whitespace_(wa_before)
			, begins_sentence_(false)
	{
#ifndef LIBTOKI_NO_TRACK_TOKEN_CREATION
		++instance_count_;
		++creation_count_;
#endif
	}

	Token::Token(const char* orth_utf8, const std::string& type, Whitespace::Enum wa_before)
			: orth_(UnicodeString::fromUTF8(orth_utf8))
			, type_(type)
			, preceeding_whitespace_(wa_before)
			, begins_sentence_(false)
	{
#ifndef LIBTOKI_NO_TRACK_TOKEN_CREATION
		++instance_count_;
		++creation_count_;
#endif
	}

	Token* Token::clone() const
	{
		return new Token(*this);
	}

	Token* Token::clone_changed(const UnicodeString &new_orth) const
	{
		Token* t = new Token(new_orth, type_, preceeding_whitespace_);
		t->set_begins_sentence(begins_sentence_);
		return t;
	}

	Token* Token::clone_changed(const UnicodeString &new_orth, std::string new_type) const
	{
		Token* t = new Token(new_orth, new_type, preceeding_whitespace_);
		t->set_begins_sentence(begins_sentence_);
		return t;
	}

	void Token::mark_as_cut()
	{
		preceeding_whitespace_ = Whitespace::None;
		begins_sentence_ = false;
	}

#ifndef LIBTOKI_NO_TRACK_TOKEN_CREATION
	Token::Token(const Token& other)
		: orth_(other.orth_), type_(other.type_),
		preceeding_whitespace_(other.preceeding_whitespace_),
		begins_sentence_(other.begins_sentence_)
	{
		++instance_count_;
	}

	Token::~Token()
	{
		--instance_count_;
	}

	int Token::creation_count_ = 0;
	int Token::instance_count_ = 0;
#endif

	std::string Token::orth_utf8() const
	{
		std::string result;
		orth_.toUTF8String(result);
		return result;
	}

} /* end namespace Toki */
