#ifndef BASICSPLITLAYER_H
#define BASICSPLITLAYER_H

#include "queuetokenlayer.h"

class BasicSplitLayer : public QueueTokenLayer
{
public:
	BasicSplitLayer(boost::shared_ptr<TokenSource> lower);

	static bool registered;

protected:
	void prepareMoreTokens();
};

#endif // BASICSPLITLAYER_H
