#ifndef LIBTOKI_COMBINELAYER_H
#define LIBTOKI_COMBINELAYER_H

#include "outputqueuelayer.h"

namespace Toki {

	/**
	 * Sample layer to glue pairs of tokens together.
	 */
	class CombineLayer : public OutputQueueLayer
	{
	public:
		/**
		 * Constructor.
		 *
		 * No new configuration keys processed. See parent class.
		 */
		CombineLayer(TokenSource* input, const Config::Node& props);

	protected:
		/// OutputQueueLayer override
		void prepare_more_tokens(Token* t);
	};

} //end namespace Toki

#endif // LIBTOKI_COMBINELAYER_H
