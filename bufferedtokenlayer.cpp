#include "bufferedtokenlayer.h"
#include "token.h"

BufferedTokenLayer::BufferedTokenLayer(TokenSource* input, const Properties& props)
	: TokenLayer(input, props), buffer_()
{
}

BufferedTokenLayer::~BufferedTokenLayer()
{
	reset();
}

void BufferedTokenLayer::reset()
{
	while (!buffer_.empty()) {
		delete buffer_.front();
		buffer_.pop();
	}
}

Token* BufferedTokenLayer::getTokenFromInput()
{
	if (buffer_.empty()) {
		return TokenLayer::getTokenFromInput();
	} else {
		Token* t = buffer_.front();
		buffer_.pop();
		return t;
	}
}

void BufferedTokenLayer::putBackToken(Token *t)
{
	buffer_.push(t);
}
