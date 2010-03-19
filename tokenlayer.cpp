#include "tokenlayer.h"

TokenLayer::TokenLayer(TokenSource* input, const Properties& /* props */)
	: input_(input)
{
}

TokenLayer::~TokenLayer()
{
}

TokenLayer* TokenLayer::create(std::string class_id, TokenSource* input, const Properties& props)
{
	return TokenLayerFactory::Instance().CreateObject(class_id, input, props);
}

Token* TokenLayer::getTokenFromInput()
{
	return input_->getNextToken();
}
