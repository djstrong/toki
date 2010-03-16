#include "combinelayer.h"

CombineLayer::CombineLayer(boost::shared_ptr<TokenLayer> lower)
	: QueueTokenLayer(lower)
{
}

void CombineLayer::reset()
{
}

void CombineLayer::prepareMoreTokens()
{
	Token* t1 = lower_->getNextToken();
	if (t1) {
		Token* t2 = lower_->getNextToken();
		if (t2) {
			t1->set_orth(t1->orth() + t2->orth());
			delete t2;
		}
		enqueueOutputToken(t1);
	}
}

namespace {
	bool registered = TokenLayerFactory::Instance().Register("split", LayerCreator<CombineLayer>);
}

