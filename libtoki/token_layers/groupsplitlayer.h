#ifndef GROUPSPLITLAYER_H
#define GROUPSPLITLAYER_H

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

	protected:
		/// OutputQueueTokenLayer override
		void prepareMoreTokens(Token* t);
	};

} /* end ns Toki */

#endif // GROUPSPLITLAYER_H
