#ifndef INPUTBUFFERLAYER_H
#define INPUTBUFFERLAYER_H

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
		Token* getTokenFromInput();

		/**
		 * Put back a received token into the buffer
		 */
		void putBackToken(Token* t);

	private:
		/// The token buffer
		std::queue<Token*> buffer_;
	};

} //end namespace Toki

#endif // INPUTBUFFERLAYER_H
