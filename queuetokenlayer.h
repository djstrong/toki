#ifndef QUEUETOKENLAYER_H
#define QUEUETOKENLAYER_H

#include "tokenlayer.h"

#include <queue>

class QueueTokenLayer : public TokenLayer
{
public:
	QueueTokenLayer(boost::shared_ptr<TokenLayer> lower);

	~QueueTokenLayer();

	Token* getNextToken();

protected:
	void enqueueOutputToken(Token* t);

	virtual void prepareMoreTokens() = 0;

private:
	std::queue<Token*> queue_;
};

#endif // QUEUETOKENLAYER_H
