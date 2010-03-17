#include "tokenlayer.h"

TokenLayer::TokenLayer(TokenSource* lower)
	: lower_(lower)
{
}

TokenLayer::~TokenLayer()
{
}

TokenLayer* TokenLayer::create(std::string class_id, TokenSource* lower)
{
	return TokenLayerFactory::Instance().CreateObject(class_id, lower);
}
