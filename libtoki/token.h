#ifndef LIBTOKI_TOKEN_H
#define LIBTOKI_TOKEN_H

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
			WA_ManyNewlines,
			WA_PostLast // last item guard
		};

		static std::string WA_as_string(WhitespaceAmount wa);

		static WhitespaceAmount WA_from_string(const std::string& s);

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

		/**
		 * Token clone
		 */
		Token* clone() const;

		/**
		 * Clone this token, changing it's orth.
		 */
		Token* clone_changed(const UnicodeString& new_orth) const;

		/**
		 * Clone this token, changing it's orth and type.
		 */
		Token* clone_changed(const UnicodeString& new_orth, const std::string new_type) const;

		/**
		 * Convenience function to set status flags to assume token had non-ws
		 * characters immediately preceding it (was 'cut' from another token).
		 */
		void mark_as_cut();

#ifdef LIBTOKI_TRACK_TOKEN_CREATION
		/// Copy ctor
		Token(const Token& other);

		/// Destructor
		~Token();

#endif
		/**
		 * Instance counter accesor, always returns -1 if the
		 * LIBTOKI_TRACK_TOKEN_CREATION symbol was not defined during compilation
		 */
		static int instance_count() {
#ifdef LIBTOKI_TRACK_TOKEN_CREATION
			return instance_count_;
#else
			return -1;
#endif
		}

		/**
		 * Creation counter accesor, always returns -1 if the
		 * LIBTOKI_TRACK_TOKEN_CREATION symbol was not defined during compilation
		 */
		static int creation_count() {
#ifdef LIBTOKI_TRACK_TOKEN_CREATION
			return creation_count_;
#else
			return -1;
#endif
		}

		/// orth getter
		const UnicodeString& orth() const {
			return orth_;
		}

		/// orth setter
		void set_orth(const UnicodeString& new_orth) {
			orth_ = new_orth;
		}

		/// type getter
		const std::string& type() const {
			return type_;
		}

		/// type setter
		void set_type(const std::string& new_type) {
			type_ = new_type;
		}

		/// wa getter
		WhitespaceAmount preceeding_whitespace() const {
			return preceeding_whitespace_;
		}

		/// wa setter
		void set_preceeding_whitespace(WhitespaceAmount new_wa) {
			preceeding_whitespace_ = new_wa;
		}

		/// orth as-utf8 convenience getter
		std::string orth_utf8() const;

		/// begins_sentence getter
		bool begins_sentence() const {
			return begins_sentence_;
		}

		/// begins_sentence setter
		void set_begins_sentence(bool v) {
			begins_sentence_ = v;
		}

	protected:
		/// 'orth', the body of the token
		UnicodeString orth_;

		/// type of the token
		std::string type_;

		/// whitespace preceeding the token
		WhitespaceAmount preceeding_whitespace_;

		/// token-begins-sentence flag
		bool begins_sentence_;

#ifdef LIBTOKI_TRACK_TOKEN_CREATION
	private:
		int instance_count_;
		int creation_count_;
#endif
	};

} /* end ns Toki */

#endif // LIBTOKI_TOKEN_H
