#ifndef COMBINELAYER_H
#define COMBINELAYER_H

#include "outputqueuelayer.h"

class CombineLayer : public OutputQueueLayer
{
public:
	CombineLayer(TokenSource* input, const Properties& props);

	static bool registered;

protected:
	void prepareMoreTokens();
};

#endif // COMBINELAYER_H
