#ifndef BASICSPLITLAYER_H
#define BASICSPLITLAYER_H

#include "queuetokenlayer.h"

class BasicSplitLayer : public QueueTokenLayer
{
public:
	BasicSplitLayer(TokenSource* input, const Properties& props);

	static bool registered;

protected:
	void prepareMoreTokens();
};

#endif // BASICSPLITLAYER_H
