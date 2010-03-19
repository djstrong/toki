#ifndef BASICSPLITLAYER_H
#define BASICSPLITLAYER_H

#include "outputqueuelayer.h"

class BasicSplitLayer : public OutputQueueLayer
{
public:
	BasicSplitLayer(TokenSource* input, const Properties& props);

	static bool registered;

protected:
	void prepareMoreTokens();
};

#endif // BASICSPLITLAYER_H
