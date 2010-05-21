#include "whitespacetokenizer.h"
#include "tokenizer.h"
#include "srx/srx.h"
#include "util.h"

#include <unicode/ucnv.h>
#include <unicode/uchar.h>
#include <fstream>
#include <iostream>

namespace Toki {

	WhitespaceTokenizer::WhitespaceTokenizer(const Config::Node &cfg)
		: Tokenizer(cfg), wa_(Whitespace::None), token_type_(),
		initial_wa_(Whitespace::None), begins_sentence_(true), srx_()
	{
		process_config(cfg);
	}

	WhitespaceTokenizer::WhitespaceTokenizer(UnicodeSource* us, const Config::Node& cfg)
		: Tokenizer(us, cfg), wa_(Whitespace::None), token_type_(),
		initial_wa_(Whitespace::None), begins_sentence_(true), srx_()
	{
		process_config(cfg);
	}

	void WhitespaceTokenizer::process_config(const Config::Node &cfg)
	{
		token_type_ = cfg.get("token_type", "t");
		std::string init_wa = cfg.get("initial_whitespace", "");
		if (init_wa.empty()) {
			initial_wa_ = Whitespace::None;
		} else {
			initial_wa_ = Whitespace::from_string(init_wa);
			if (initial_wa_ == Whitespace::PostLast) {
				std::cerr << "Bad initial whitespace value:" << init_wa << "\n";
				initial_wa_ = Whitespace::None;
			}
		}
		std::string srx = cfg.get("srx", "");
		if (!srx.empty()) {
			std::ifstream ifs;
			Config::open_file_from_search_path(srx, ifs);
			Srx::Document d;
			d.load(ifs);
			std::string srx_lang = cfg.get("srx_language", "");
			std::vector<Srx::Rule> rules;
			if (srx_lang.empty()) {
				rules = d.get_all_rules();
			} else {
				rules = d.get_rules_for_lang(srx_lang);
			}
			boost::shared_ptr<Srx::Segmenter> segm(new Srx::NaiveIcuSegmenter());
			segm->load_rules(rules);
			int window = cfg.get("srx_window", 10000);
			int margin = cfg.get("srx_margin", 100);
			boost::shared_ptr<Srx::SourceWrapper> u;
			u.reset(new Srx::SourceWrapper(get_input_source(), segm, window, margin));
			set_input_source(u);
			srx_ = u;
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
		if (srx_) {
			srx_->set_source(get_input_source());
			input_ = srx_;
		}
	}


	void WhitespaceTokenizer::eat_whitespace()
	{
		int ws = 0; int nl = 0;
		while (input().has_more_chars()) {
			UChar u = input().peek_next_char();
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
			wa_ = Whitespace::ManyNewlines;
		} else if (nl == 1) {
			wa_ = Whitespace::Newline;
		} else if (ws > 1) {
			wa_ = Whitespace::ManySpaces;
		} else if (ws == 1) {
			wa_ = Whitespace::Space;
		} else {
			wa_ = initial_wa_;
		}
	}

	Token* WhitespaceTokenizer::get_next_token()
	{
		if (!input().has_more_chars()) {
			return NULL;
		}
		eat_whitespace();
		UnicodeString orth;
		if (input().has_more_chars()) {
			bool next_token_begins_sentence = false;
			UChar u = input().get_next_char();
			orth = u;
			while (input().has_more_chars()) {
				//std::string ou = Util::to_utf8(orth);
				//std::cerr << ou;
				u = input().peek_next_char();
				if (u_isUWhiteSpace(u)) {
					if (input().peek_begins_sentence()) {
						next_token_begins_sentence = true;
					}
					break;
				} else if (input().peek_begins_sentence()) {
					next_token_begins_sentence = true;
					break;
				} else {
					orth += u;
					input().get_next_char();
				}
			}
			Token* t  = new Token(orth, token_type_, wa_);
			t->set_begins_sentence(begins_sentence_);
			begins_sentence_ = next_token_begins_sentence;
			return t;
		} else {
			return NULL;
		}
	}

} /* end namespace Toki */
