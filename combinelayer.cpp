#include "combinelayer.h"
#include "token.h"

CombineLayer::CombineLayer(TokenSource* input, const Properties& props)
	: QueueTokenLayer(input, props)
{
}

void CombineLayer::prepareMoreTokens()
{
	Token* t1 = getTokenFromInput();
	if (t1) {
		Token* t2 = getTokenFromInput();
		if (t2) {
			t1->set_orth(t1->orth() + t2->orth());
			delete t2;
		}
		enqueueOutputToken(t1);
	}
}

bool CombineLayer::registered = TokenLayer::register_layer<CombineLayer>("combine");


