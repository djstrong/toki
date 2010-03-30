#ifndef COMBINELAYER_H
#define COMBINELAYER_H

#include "outputqueuelayer.h"

class CombineLayer : public OutputQueueLayer
{
public:
	CombineLayer(TokenSource* input, const Config::Node& props);

protected:
	void prepareMoreTokens(Token* t);
};

#endif // COMBINELAYER_H
