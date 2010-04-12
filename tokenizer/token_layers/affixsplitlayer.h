#ifndef AFFIXSPLITLAYER_H
#define AFFIXSPLITLAYER_H

#include "outputqueuelayer.h"

#include <set>

namespace Toki {

	/**
	 * Layer to recognize and split prefix and posftix characters in tokens.
	 * All prefix characters are extracted as separate tokens, then the unrecognized
	 * part is output as the body token (with the type unmodified), and then the
	 * suffix characters are output.
	 */
	class AffixSplitLayer : public OutputQueueLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * Keys recognized in the configuration:
		 * - prefix_chars  - List of prefix characters, treated as UTF-8 and
		 *                   unescaped. Defaults to empty.
		 * - suffix_chars - List of suffix characters, treated as UTF-8 and
		 *                   unescaped. Defaults to empty.
		 * - prefix_token_type  - Token type to set in the extracted prefixes.
		 *                        Defaults to "pre".
		 * - suffix_token_type - Token type to set in the extracted suffixes.
		 *                        Defaults to "post".
		 */

		AffixSplitLayer(TokenSource* input, const Config::Node& props);

		/// TokenLayer override
		virtual std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

	protected:
		/// OutputQueueLayer override
		void prepareMoreTokens(Token* t);

	private:
		/// test function for prefix characters
		bool isPrefixChar(UChar c);

		/// test function for suffix characters
		bool isPostfixChar(UChar c);

		/// prefix characters
		std::set<UChar> prefix_chars_;

		/// suffix characters
		std::set<UChar> suffix_chars_;

		/// type of the extracted prefix tokens
		std::string prefix_type_;

		/// type of the extracted suffix tokens
		std::string suffix_type_;
	};

} //end namespace Toki

#endif // AFFIXSPLITLAYER_H
