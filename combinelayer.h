#ifndef COMBINELAYER_H
#define COMBINELAYER_H

#include "queuetokenlayer.h"

class CombineLayer : public QueueTokenLayer
{
public:
    CombineLayer(boost::shared_ptr<TokenLayer> lower);

	void reset();

protected:
	void prepareMoreTokens();
};

#endif // COMBINELAYER_H
