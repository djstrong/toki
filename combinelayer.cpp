#include "combinelayer.h"
#include "token.h"

CombineLayer::CombineLayer(TokenSource* input)
	: QueueTokenLayer(input)
{
}

void CombineLayer::prepareMoreTokens()
{
	Token* t1 = input_->getNextToken();
	if (t1) {
		Token* t2 = input_->getNextToken();
		if (t2) {
			t1->set_orth(t1->orth() + t2->orth());
			delete t2;
		}
		enqueueOutputToken(t1);
	}
}

bool CombineLayer::registered = TokenLayer::register_layer<CombineLayer>("combine");


