#include "basicsplitlayer.h"
#include "token.h"

BasicSplitLayer::BasicSplitLayer(TokenSource* input)
	: QueueTokenLayer(input)
{
}

void BasicSplitLayer::prepareMoreTokens()
{
	Token* t = input_->getNextToken();
	if (t) {
		// do stuff with t, split etc
		t->set_orth(t->orth() + "!!!");
		enqueueOutputToken(t);
	}
}

bool BasicSplitLayer::registered = TokenLayer::register_layer<BasicSplitLayer>("split");
