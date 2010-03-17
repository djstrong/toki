#include "basicsplitlayer.h"
#include "token.h"

BasicSplitLayer::BasicSplitLayer(TokenSource* lower)
	: QueueTokenLayer(lower)
{
}

void BasicSplitLayer::prepareMoreTokens()
{
	Token* t = lower_->getNextToken();
	if (t) {
		// do stuff with t, split etc
		t->set_orth(t->orth() + "!!!");
		enqueueOutputToken(t);
	}
}

bool BasicSplitLayer::registered = TokenLayer::register_layer<BasicSplitLayer>("split");
