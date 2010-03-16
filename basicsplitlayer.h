#ifndef BASICSPLITLAYER_H
#define BASICSPLITLAYER_H

#include "queuetokenlayer.h"

class BasicSplitLayer : public QueueTokenLayer
{
public:
	BasicSplitLayer(boost::shared_ptr<TokenLayer> lower);

	void reset();

protected:
	void prepareMoreTokens();
};

#endif // BASICSPLITLAYER_H
