#ifndef COMBINELAYER_H
#define COMBINELAYER_H

#include "outputqueuelayer.h"

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

#endif // COMBINELAYER_H
