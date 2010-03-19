#ifndef BUFFEREDTOKENLAYER_H
#define BUFFEREDTOKENLAYER_H

#include "tokenlayer.h"
#include <queue>

class BufferedTokenLayer : public TokenLayer
{
public:
	BufferedTokenLayer(TokenSource* input, const Properties& props);

	~BufferedTokenLayer();

	void reset();

protected:
	Token* getTokenFromInput();

	void putBackToken(Token* t);

private:
	std::queue<Token*> buffer_;
};

#endif // BUFFEREDTOKENLAYER_H
