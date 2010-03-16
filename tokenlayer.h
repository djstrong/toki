#ifndef TOKENLAYER_H
#define TOKENLAYER_H

#include "tokensource.h"

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <loki/Factory.h>
#include <loki/Singleton.h>


/**
 * A token layer processes tokens form a source and allows getting the processed
 * tokens, so a layer is a token source itself.
 *
 * Layers are designed to be dynamically created by a factory based on unique
 * string class identifires. To register a derived Layer class, add a static
 * bool member e.g. \c registered to the class, and initialize it in the layer's
 * source file as follows:
 * @code
 * bool MyLayer::registered = TokenLayer::register_type<MyLayer>("my_layer_id");
 * @endcode
 * The constructor of the derived class should take the same arguments.
 */
class TokenLayer : public TokenSource, private boost::noncopyable
{
public:
	/**
	 * The constructor.
	 * @param lower The token source this layer will process tokens from.
	 */
	TokenLayer(boost::shared_ptr<TokenSource> lower);

	/// The destructor
	virtual ~TokenLayer();

	/**
	 * Getter for the used source.
	 */
	boost::shared_ptr<TokenSource> getSource();

	/**
	 * Reset this layer's state so when a token is requested it will start over,
	 * processing tokens from the underlying source just like it was just
	 * constructed.
	 *
	 * Derived classes should override this to maintain this requirement, and
	 * always call the parent class' reset().
	 */
	virtual void reset() = 0;

	/**
	 * Factory interface for creating layers from string identifiers
	 *
	 * Mostly a convenience function to avoid having client code refer directly
	 * to the TokenLayerFactory instance.
	 *
	 * @param class_id the unique class identifier
	 * @param lower the underlying layer to pass to the layer's constructor
	 */
	static TokenLayer* create(const std::string class_id,
	                          boost::shared_ptr<TokenSource> lower);

	/**
	 * Convenience template for registering TokenLayer derived classes.
	 */
	template <typename T>
	static bool register_layer(const std::string& class_id);

protected:
	/**
	 * Pointer to the source TokenSource (e.g. a layer)
	 */
	boost::shared_ptr<TokenSource> lower_;
};

/**
 * Declaration of the TokenLayer factory as a singleton Loki object factory.
 * The factory instance can be accessed as TokenLayerFactory::Instance().
 * It is assumed that all derived classes have the same constructor signature.
 */
typedef Loki::SingletonHolder<
	Loki::Factory<
		TokenLayer, // The base class for objects created in the factory
		std::string, // Identifier type
		Loki::TL::MakeTypelist< boost::shared_ptr<TokenSource> >::Result
		// TokenLayer constructor arguments' types specification
	>,
	Loki::CreateUsingNew, // Default, needed to change the item below
	Loki::LongevityLifetime::DieAsSmallObjectChild // Required per libloki docs
>
TokenLayerFactory;

/**
 * Convenience template TokenLayer creation function
 */
template <typename T>
inline
T* LayerCreator(boost::shared_ptr<TokenSource> lower)
{
	return new T(lower);
}

template <typename T>
bool TokenLayer::register_layer(const std::string& class_id)
{
	return TokenLayerFactory::Instance().Register(class_id, LayerCreator<T>);
}


#endif // TOKENLAYER_H
