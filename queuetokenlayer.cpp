#include "queuetokenlayer.h"
#include <cassert>

QueueTokenLayer::QueueTokenLayer(boost::shared_ptr<TokenLayer> lower)
	: TokenLayer(lower), queue_()
{
}

QueueTokenLayer::~QueueTokenLayer()
{
}

void QueueTokenLayer::enqueueOutputToken(Token *t)
{
	assert(t);
	queue_.push(t);
}

Token* QueueTokenLayer::getNextToken()
{
	if (queue_.empty()) {
		prepareMoreTokens();
	}
	if (queue_.empty()) {
		return NULL;
	} else {
		Token* t = queue_.front();
		queue_.pop();
		return t;
	}
}

