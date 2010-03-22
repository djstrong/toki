#include "combinelayer.h"
#include "token.h"

CombineLayer::CombineLayer(TokenSource* input, const Properties& props)
	: OutputQueueLayer(input, props)
{
}

void CombineLayer::prepareMoreTokens(Token* t)
{
	Token* t2 = getTokenFromInput();
	if (t2) {
		t->set_orth(t->orth() + t2->orth());
		delete t2;
	}
	enqueueOutputToken(t);
}

bool CombineLayer::registered = TokenLayer::register_layer<CombineLayer>("combine");


