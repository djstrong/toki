#ifndef LIBTOKI_OUTPUTQUEUELAYER_H
#define LIBTOKI_OUTPUTQUEUELAYER_H

#include "tokenlayer.h"

#include <queue>

namespace Toki {

	/**
	 * A base class for queue-based token layers that work by consuming tokens from
	 * the source, processing them, and adding processed tokens to an output queue.
	 */
	class OutputQueueLayer : public TokenLayer
	{
	public:
		/// Consructor
		OutputQueueLayer(TokenSource* input, const Config::Node& props);

		/// Destructor
		~OutputQueueLayer();

		/**
		 * TokenSource override. Returns the front element from the queue if any,
		 * otherwise grabs a token from he input, checks it for NULL and
		 * checks shouldProcessTokenType, and then calls prepareMoreTokens() before
		 * trying to return the front element from the queue again.
		 * @return a Token, or NULL if the queue was empty and prepareMoreTokens()
		 *         did not call enqueueOutputToken() at least once.
		 */
		Token* getNextToken();

		/**
		 * TokenLayer override. Destroys the output token queue.
		 */
		void reset();

		/// TokenLayer override
		std::string long_info() const;

	protected:
		/**
		 * Add an token to the output queue. Derived classes should use this to
		 * push ready tokens to the output from within prepareMoreTokens().
		 */
		void enqueueOutputToken(Token* t);

		/**
		 * Derived classes should override this with code that consumes tokens from
		 * the source as many times as it is necessary to have at least one token
		 * ready (=call enqueueOutputToken() at least once). The argument is a
		 * token grabbed from the input source, guaranteed to be not null, and
		 * type-checked by shouldProcessTokenType.
		 *
		 * The derived class should either delete this token or enqueue it, and may
		 * call getTokenFromInput to get more tokens if necessary (but should check
		 * for NULL and shouldProcessTokenType() in that case).
		 *
		 * If enqueueOutputToken() is not called, getNextToken will end up returning
		 * NULL which will signal an end of tokens to the client.
		 * @param t token to process, guaranteed to be not NULL
		 */
		virtual void prepareMoreTokens(Token* t) = 0;

	private:
		/**
		 * Remove all tokens from the queue and dispose of them
		 */
		void clear_queue();

		/// The queue of tokens ready to be returned by getNextToken
		std::queue<Token*> queue_;
	};

} //end namespace Toki

#endif // LIBTOKI_OUTPUTQUEUELAYER_H
