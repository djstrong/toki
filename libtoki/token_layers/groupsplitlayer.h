#ifndef LIBTOKI_GROUPSPLITLAYER_H
#define LIBTOKI_GROUPSPLITLAYER_H

#include "basicsplitlayer.h"

namespace Toki {

	class GroupSplitLayer : public BasicSplitLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * No new configuration keys processed.
		 */
		GroupSplitLayer(TokenSource* input, const Config::Node& props);

		/// TokenLayer override
		std::string info() const;

		/// TokenLayer override
		std::string long_info() const;

	protected:
		/// OutputQueueTokenLayer override
		void prepareMoreTokens(Token* t);
	};

} /* end ns Toki */

#endif // LIBTOKI_GROUPSPLITLAYER_H
