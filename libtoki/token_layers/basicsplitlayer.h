#ifndef LIBTOKI_BASICSPLITLAYER_H
#define LIBTOKI_BASICSPLITLAYER_H

#include "outputqueuelayer.h"
#include <set>
#include <unicode/utypes.h>

namespace Toki {

	/**
	 * A layer to split tokens containing one of the listed characters. Extracted
	 * characters are made into separate tokens with a given type, remaining bits
	 * of the orth are made tokens with the original token's type.
	 */
	class BasicSplitLayer : public OutputQueueLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * Keys recognized in the configuration:
		 * - separators - List of characters treated as spearators, treated as UTF-8
		 *                and unescaped. default_configs to empty.
		 * - separator_token_type - Type to set in the separator tokens. default_configs
		 *                          to "sep".
		 */
		BasicSplitLayer(TokenSource* input, const Config::Node& props);

		/// TokenLayer override
		virtual std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

		/// getter for the separator type
		const std::string& separator_type() const {
			return sep_type_;
		}
		/// getter for the separators set
		const std::set<UChar>& separators() const {
			return split_chars_;
		}

	protected:
		/// OutputQueueTokenLayer override
		void prepareMoreTokens(Token* t);

		/// test function for the split chars
		bool isSplitChar(UChar c);

	private:
		/// the split characters
		std::set<UChar> split_chars_;

		/// type of the extracted tokens
		std::string sep_type_;
	};

} //end namespace Toki

#endif // LIBTOKI_BASICSPLITLAYER_H
