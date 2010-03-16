#ifndef COMBINELAYER_H
#define COMBINELAYER_H

#include "queuetokenlayer.h"

class CombineLayer : public QueueTokenLayer
{
public:
	CombineLayer(boost::shared_ptr<TokenSource> lower);

	static bool registered;

protected:
	void prepareMoreTokens();
};

#endif // COMBINELAYER_H
