#include "combinelayer.h"
#include "token.h"

CombineLayer::CombineLayer(boost::shared_ptr<TokenSource> lower)
	: QueueTokenLayer(lower)
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

bool CombineLayer::registered = TokenLayer::register_layer<CombineLayer>("combine");


