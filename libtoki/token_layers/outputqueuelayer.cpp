#include "outputqueuelayer.h"
#include "token.h"
#include <cassert>

namespace Toki {

	OutputQueueLayer::OutputQueueLayer(TokenSource* input, const Config::Node& props)
		: TokenLayer(input, props), queue_()
	{
	}

	OutputQueueLayer::~OutputQueueLayer()
	{
		clear_queue();
	}

	void OutputQueueLayer::enqueueOutputToken(Token *t)
	{
		assert(t);
		queue_.push(t);
	}

	Token* OutputQueueLayer::get_next_token()
	{
		if (queue_.empty()) {
			Token* t = getTokenFromInput();
			if (t) {
				if (shouldProcessTokenType(t->type())) {
					prepareMoreTokens(t);
				} else {
					enqueueOutputToken(t);
				}
			}
		}
		if (queue_.empty()) {
			return NULL;
		} else {
			Token* t = queue_.front();
			queue_.pop();
			return t;
		}
	}

	void OutputQueueLayer::clear_queue()
	{
		while (!queue_.empty()) {
			Token* t = queue_.front();
			delete t;
			queue_.pop();
		}
	}

	void OutputQueueLayer::reset()
	{
		clear_queue();
	}

	std::string OutputQueueLayer::long_info() const
	{
		std::stringstream ss;
		ss << ", out_queue(" << queue_.size() << ")";
		return TokenLayer::long_info() + ss.str();
	}

} /* end namespace Toki */
