#include "basicsplitlayer.h"

BasicSplitLayer::BasicSplitLayer(boost::shared_ptr<TokenLayer> lower)
	: QueueTokenLayer(lower)
{
}

void BasicSplitLayer::reset()
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

namespace {
	bool registered = TokenLayerFactory::Instance().Register("split", LayerCreator<BasicSplitLayer>);
}
