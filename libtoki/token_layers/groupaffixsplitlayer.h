#ifndef LIBTOKI_GROUPAFFIXSPLITLAYER_H
#define LIBTOKI_GROUPAFFIXSPLITLAYER_H

#include "affixsplitlayer.h"

namespace Toki {

	/**
	 * Layer to recognize and split prefix and posftix characters in tokens.
	 * All prefix characters are extracted as one token, then the unrecognized
	 * part is output as the body token (with the type unmodified), and then the
	 * suffix characters are output as the suffix token. This layer works a lot
	 * like AffisSpliLayer with the difference being that the extracted pre- and
	 * suffixes are not split into one-letter tokens. Also see GroupSplitLayer.
	 */
	class GroupAffixSplitLayer : public AffixSplitLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * No new configuration keys processed. See parent class.
		 */
		GroupAffixSplitLayer(TokenSource* input, const Config::Node& props);

		/// TokenLayer override
		std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

	protected:
		/// OutputQueueTokenLayer override
		void prepare_more_tokens(Token* t);
	};

} /* end ns Toki */


#endif // LIBTOKI_GROUPAFFIXSPLITLAYER_H
