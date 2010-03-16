#include "basicsplitlayer.h"

BasicSplitLayer::BasicSplitLayer(boost::shared_ptr<TokenSource> lower)
	: QueueTokenLayer(lower)
{
}

void BasicSplitLayer::prepareMoreTokens()
{
	Token* t = lower_->getNextToken();
	// do stuff with t, split etc
	if (t) {
		enqueueOutputToken(t);
	}
}

bool BasicSplitLayer::registered = TokenLayer::register_layer<BasicSplitLayer>("split");
