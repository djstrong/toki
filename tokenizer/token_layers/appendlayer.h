#ifndef APPENDLAYER_H
#define APPENDLAYER_H

#include "tokenlayer.h"
#include <unicode/unistr.h>

class AppendLayer : public TokenLayer
{
public:
	AppendLayer(TokenSource* input, const Properties& props);

	Token* getNextToken();

	static bool registered;

private:
	UnicodeString append_;
};

#endif // APPENDLAYER_H
