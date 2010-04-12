#ifndef TOKEN_H
#define TOKEN_H

#include <unicode/unistr.h>
#include <string>

namespace Toki {

	/**
	 * A single token being processed. The orth is stored as an ICU UnicodeString.
	 */
	class Token
	{
	public:
		enum WhitespaceAmount {
			WA_None,
			WA_Space,
			WA_ManySpaces,
			WA_Newline,
			WA_ManyNewlines
		};

		static std::string WA_as_string(WhitespaceAmount wa);

		/**
		 * Constructor.
		 * @param orth      the token orth
		 * @param type      the token type
		 * @param wa_before preceeding whitespace amount indicator
		 */
		Token(const UnicodeString& orth, const std::string& type, WhitespaceAmount wa_before);

		/**
		 * Constructor.
		 * @param orth_utf8 the token orth, treated as an UTF8
		 * @param type      the token type
		 * @param wa_before preceeding whitespace amount indicator
		 */
		Token(const char* orth_utf8, const std::string& type, WhitespaceAmount wa_before);

		const UnicodeString& orth() const {
			return orth_;
		}

		void set_orth(const UnicodeString& new_orth) {
			orth_ = new_orth;
		}

		const std::string& type() const {
			return type_;
		}

		void set_type(const std::string& new_type) {
			type_ = new_type;
		}

		WhitespaceAmount preceeding_whitespace() const {
			return preceeding_whitespace_;
		}

		void set_preceeding_whitespace(WhitespaceAmount new_wa) {
			preceeding_whitespace_ = new_wa;
		}

		std::string orth_utf8() const;

	protected:
		UnicodeString orth_;
		std::string type_;
		WhitespaceAmount preceeding_whitespace_;
	};

} /* end ns Toki */

#endif // TOKEN_H
