#include "tokenlayer.h"

TokenLayer::TokenLayer()
	: lower_()
{
}

TokenLayer::TokenLayer(boost::shared_ptr<TokenLayer>lower)
	: lower_(lower)
{
}

TokenLayer::~TokenLayer()
{
}

TokenLayer* TokenLayer::create(std::string class_id, boost::shared_ptr<TokenLayer>lower)
{
	return TokenLayerFactory::Instance().CreateObject(class_id, lower);
}
