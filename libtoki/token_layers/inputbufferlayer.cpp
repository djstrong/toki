#include "inputbufferlayer.h"
#include "token.h"

namespace Toki {

	InputBufferLayer::InputBufferLayer(TokenSource* input, const Config::Node& props)
		: TokenLayer(input, props), buffer_()
	{
	}

	InputBufferLayer::~InputBufferLayer()
	{
		reset();
	}

	void InputBufferLayer::reset()
	{
		while (!buffer_.empty()) {
			delete buffer_.front();
			buffer_.pop();
		}
	}

	std::string InputBufferLayer::long_info() const
	{
		std::stringstream ss;
		ss << ", input_buffer(" << buffer_.size() << ")";
		return TokenLayer::long_info() + ss.str();
	}

	Token* InputBufferLayer::get_token_from_input()
	{
		if (buffer_.empty()) {
			return TokenLayer::get_token_from_input();
		} else {
			Token* t = buffer_.front();
			buffer_.pop();
			return t;
		}
	}

	void InputBufferLayer::put_back_token(Token *t)
	{
		buffer_.push(t);
	}

} /* end namespace Toki */
