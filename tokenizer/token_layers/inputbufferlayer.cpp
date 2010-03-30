#include "inputbufferlayer.h"
#include "token.h"

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

Token* InputBufferLayer::getTokenFromInput()
{
	if (buffer_.empty()) {
		return TokenLayer::getTokenFromInput();
	} else {
		Token* t = buffer_.front();
		buffer_.pop();
		return t;
	}
}

void InputBufferLayer::putBackToken(Token *t)
{
	buffer_.push(t);
}
