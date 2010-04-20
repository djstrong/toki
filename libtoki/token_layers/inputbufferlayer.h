#ifndef LIBTOKI_INPUTBUFFERLAYER_H
#define LIBTOKI_INPUTBUFFERLAYER_H

#include "tokenlayer.h"
#include <queue>

namespace Toki {

	/**
	 * A base class for layers that might want to look ahead into the token source
	 * but might not always want to consume all the tokens.
	 */
	class InputBufferLayer : public TokenLayer
	{
	public:
		/**
		 * Constructor. No config keys recognized.
		 */
		InputBufferLayer(TokenSource* input, const Config::Node& props);

		/// Destructor
		~InputBufferLayer();

		/// reset function
		void reset();

		/// TokenLayer override
		std::string long_info() const;

	protected:
		/**
		 * TokenLayer override that uses the buffer.
		 */
		Token* get_token_from_input();

		/**
		 * Put back a received token into the buffer
		 */
		void put_back_token(Token* t);

	private:
		/// The token buffer
		std::queue<Token*> buffer_;
	};

} //end namespace Toki

#endif // LIBTOKI_INPUTBUFFERLAYER_H
