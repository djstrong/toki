#ifndef TOKENLAYER_H
#define TOKENLAYER_H

#include <boost/shared_ptr.hpp>
#include <loki/Factory.h>
#include <loki/Singleton.h>

#include "token.h"

class TokenLayer
{
public:
	TokenLayer();

	TokenLayer(boost::shared_ptr<TokenLayer> lower);

	virtual ~TokenLayer();

	virtual Token* getNextToken() = 0;

	boost::shared_ptr<TokenLayer> getLowerLayer();

	virtual void reset() = 0;

	static TokenLayer* create(const std::string class_id, boost::shared_ptr<TokenLayer> lower);

protected:
	boost::shared_ptr<TokenLayer> lower_;
};

typedef Loki::SingletonHolder<
	Loki::Factory<
		TokenLayer,
		std::string,
		Loki::TL::MakeTypelist< boost::shared_ptr<TokenLayer> >::Result
	>,
	Loki::CreateUsingNew,
	Loki::LongevityLifetime::DieAsSmallObjectChild
>
TokenLayerFactory;



template <typename T>
inline
T* LayerCreator(boost::shared_ptr<TokenLayer> lower)
{
	return new T(lower);
}


#endif // TOKENLAYER_H
