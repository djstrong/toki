#ifndef LIBTOKI_AFFIXSPLITLAYER_H
#define LIBTOKI_AFFIXSPLITLAYER_H

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
		 *                   unescaped. default_configs to empty.
		 * - suffix_chars - List of suffix characters, treated as UTF-8 and
		 *                   unescaped. default_configs to empty.
		 * - prefix_token_type  - Token type to set in the extracted prefixes.
		 *                        default_configs to "pre".
		 * - suffix_token_type - Token type to set in the extracted suffixes.
		 *                        default_configs to "post".
		 */

		AffixSplitLayer(TokenSource* input, const Config::Node& props);

		/// TokenLayer override
		virtual std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

	protected:
		/// OutputQueueLayer override
		void prepare_more_tokens(Token* t);

	private:
		/// test function for prefix characters
		bool is_prefix_char(UChar c);

		/// test function for suffix characters
		bool is_suffix_char(UChar c);

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

#endif // LIBTOKI_AFFIXSPLITLAYER_H
