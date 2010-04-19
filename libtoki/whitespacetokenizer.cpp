#include "whitespacetokenizer.h"
#include "tokenizer.h"

#include <unicode/ucnv.h>
#include <unicode/uchar.h>
#include <iostream>

namespace Toki {

	WhitespaceTokenizer::WhitespaceTokenizer(const Config::Node &cfg)
		: Tokenizer(cfg), wa_(Token::WA_None), token_type_(),
		initial_wa_(Token::WA_None), begins_sentence_(true)
	{
		process_config(cfg);
	}

	WhitespaceTokenizer::WhitespaceTokenizer(UnicodeSource* us, const Config::Node& cfg)
		: Tokenizer(us, cfg), wa_(Token::WA_None), token_type_(),
		initial_wa_(Token::WA_None), begins_sentence_(true)
	{
		process_config(cfg);
	}

	void WhitespaceTokenizer::process_config(const Config::Node &cfg)
	{
		token_type_ = cfg.get("token_type", "t");
		std::string init_wa = cfg.get("initial_whitespace", "");
		if (init_wa.empty()) {
			initial_wa_ = Token::WA_None;
		} else {
			initial_wa_ = Token::WA_from_string(init_wa);
			if (initial_wa_ == Token::WA_PostLast) {
				std::cerr << "Bad initial whitespace value:" << init_wa << "\n";
				initial_wa_ = Token::WA_None;
			}
		}
		wa_ = initial_wa_;
	}

	void WhitespaceTokenizer::reset()
	{
		wa_ = initial_wa_;
		begins_sentence_ = true;
	}

	void WhitespaceTokenizer::new_input_source()
	{
	}


	void WhitespaceTokenizer::eatWhitespace()
	{
		int ws = 0; int nl = 0;
		while (input().has_more_chars()) {
			UChar u = input_->peek_next_char();
			if (!u_isUWhiteSpace(u)) {
				break;
			} else {
				ws++;
				if (u == 0xA || u == 0x2029 || u == 0x2028) {
					nl++;
				}
				input().get_next_char();
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
			wa_ = initial_wa_;
		}
	}

	Token* WhitespaceTokenizer::get_next_token()
	{
		if (!input().has_more_chars()) {
			return NULL;
		}
		eatWhitespace();
		UnicodeString orth;
		if (input().has_more_chars()) {
			UChar u = input().get_next_char();
			orth = u;
			while (input().has_more_chars()) {
				u = input().peek_next_char();
				if (u_isUWhiteSpace(u)) {
					break;
				} else {
					orth += u;
					input().get_next_char();
				}
			}
			Token* t  = new Token(orth, token_type_, wa_);
			t->set_begins_sentence(begins_sentence_);
			begins_sentence_ = false;
			return t;
		} else {
			return NULL;
		}
	}

} /* end namespace Toki */
