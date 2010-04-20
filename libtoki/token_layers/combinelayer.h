#ifndef LIBTOKI_COMBINELAYER_H
#define LIBTOKI_COMBINELAYER_H

#include "outputqueuelayer.h"

namespace Toki {

	/**
	 * Sample layer to glue pairs of tokens together.
	 */
	class CombineLayer : public OutputQueueLayer
	{
	public:
		CombineLayer(TokenSource* input, const Config::Node& props);

	protected:
		void prepare_more_tokens(Token* t);
	};

} //end namespace Toki

#endif // LIBTOKI_COMBINELAYER_H
