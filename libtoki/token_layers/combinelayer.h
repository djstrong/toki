#ifndef COMBINELAYER_H
#define COMBINELAYER_H

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
		void prepareMoreTokens(Token* t);
	};

} //end namespace Toki

#endif // COMBINELAYER_H
