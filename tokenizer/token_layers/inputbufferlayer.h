#ifndef INPUTBUFFERLAYER_H
#define INPUTBUFFERLAYER_H

#include "tokenlayer.h"
#include <queue>

class InputBufferLayer : public TokenLayer
{
public:
	InputBufferLayer(TokenSource* input, const Properties& props);

	~InputBufferLayer();

	void reset();

protected:
	Token* getTokenFromInput();

	void putBackToken(Token* t);

private:
	std::queue<Token*> buffer_;
};

#endif // INPUTBUFFERLAYER_H
