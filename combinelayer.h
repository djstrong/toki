#ifndef COMBINELAYER_H
#define COMBINELAYER_H

#include "queuetokenlayer.h"

class CombineLayer : public QueueTokenLayer
{
public:
	CombineLayer(TokenSource* input, const Properties& props);

	static bool registered;

protected:
	void prepareMoreTokens();
};

#endif // COMBINELAYER_H
