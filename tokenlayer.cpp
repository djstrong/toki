#include "tokenlayer.h"

TokenLayer::TokenLayer(TokenSource* input)
	: input_(input)
{
}

TokenLayer::~TokenLayer()
{
}

TokenLayer* TokenLayer::create(std::string class_id, TokenSource* input)
{
	return TokenLayerFactory::Instance().CreateObject(class_id, input);
}
