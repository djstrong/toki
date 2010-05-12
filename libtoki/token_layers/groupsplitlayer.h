#ifndef LIBTOKI_GROUPSPLITLAYER_H
#define LIBTOKI_GROUPSPLITLAYER_H

#include "basicsplitlayer.h"

namespace Toki {

	/**
	 * A layer to split tokens containing one of the listed characters. Matching
	 * characters are extracted into continous tokens with a given type, remaining
	 * bits of the orth are made into tokens with the original token's type.
	 * This layer works a lot like BasicSplitLayer, with the difference being
	 * that the extracted separators are notsplit into one-letter tokens but
	 * held together, so if a dot -- . -- is a separator the token "aa..bb" will
	 * be split into three tokens: "aa", "..", and "bb".
	 */
	class GroupSplitLayer : public BasicSplitLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * No new configuration keys processed. See parent class.
		 */
		GroupSplitLayer(TokenSource* input, const Config::Node& props);

		/// TokenLayer override
		std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

	protected:
		/// OutputQueueTokenLayer override
		void prepare_more_tokens(Token* t);
	};

} /* end ns Toki */

#endif // LIBTOKI_GROUPSPLITLAYER_H
