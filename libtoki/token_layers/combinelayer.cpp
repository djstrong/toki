#include "combinelayer.h"
#include "token.h"

namespace Toki {

	CombineLayer::CombineLayer(TokenSource* input, const Config::Node& props)
		: OutputQueueLayer(input, props)
	{
	}

	void CombineLayer::prepare_more_tokens(Token* t)
	{
		Token* t2 = get_token_from_input();
		if (t2) {
			t->set_orth(t->orth() + t2->orth());
			delete t2;
		}
		enqueue_output_token(t);
	}

} /* end namespace Toki */
