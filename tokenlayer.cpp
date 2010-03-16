#include "tokenlayer.h"

TokenLayer::TokenLayer(boost::shared_ptr<TokenSource>lower)
	: lower_(lower)
{
}

TokenLayer::~TokenLayer()
{
}

TokenLayer* TokenLayer::create(std::string class_id, boost::shared_ptr<TokenSource>lower)
{
	return TokenLayerFactory::Instance().CreateObject(class_id, lower);
}
