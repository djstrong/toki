#ifndef TOKENLAYER_H
#define TOKENLAYER_H

#include "tokensource.h"

#include <boost/utility.hpp>
#include <loki/Factory.h>
#include <loki/Singleton.h>

#include <boost/property_tree/ptree_fwd.hpp>

#include <set>

/**
 * A token layer processes tokens from some input source (TokenSource) and
 * allows getting the processed tokens, so a layer is a token source itself.
 * This allows stacking -- or layering -- TokenLayers.
 *
 * The constructor of the derived class should take the same arguments as the
 * base TokenLayer does, and should pass them upwards.
 *
 * Layers are designed to be dynamically created by a factory based on unique
 * string class identifires. To register a derived Layer class, add a call
 * @code
 * TokenLayer::register_type<MyLayer>("my_layer_id")
 * @code
 * in the init_token_layers() function.
 *
 * Client code might add a static bool member e.g. \c registered to the class,
 * and initialize it in the layer's source file as follows:
 * @code
 * bool MyLayer::registered = TokenLayer::register_type<MyLayer>("my_layer_id");
 * @endcode
 * Note however that due to C++ dynamic initalization order, it is not generally
 * safe to rely on this trick to always work, especially when linking to a
 * library -- the dynamic initialization of static members in a library that is
 * being linked to statically can happen *after* the beginning of main(). In
 * particular, having the layers in the library register themselves in such
 * manner does not work when statically linking the library in gcc 4.4.1.
 */
class TokenLayer : public TokenSource, private boost::noncopyable
{
public:
	typedef boost::property_tree::ptree Properties;

	/**
	 * The constructor.
	 * @param input The token source this layer will process tokens from.
	 */
	TokenLayer(TokenSource* input, const Properties& props);

	/// The destructor
	virtual ~TokenLayer();

	/**
	 * Getter for the input source.
	 */
	TokenSource* getInput();

	/**
	 * Reset this layer's state so when a token is requested it will start over,
	 * processing tokens from the input source just like it was just
	 * constructed.
	 *
	 * Note that It does *NOT* automatically call reset() on the input source.
	 *
	 * Derived classes should override this to maintain this requirement, and
	 * always call the parent class' reset().
	 */
	virtual void reset();

	/**
	 * Factory interface for creating layers from string identifiers
	 *
	 * Mostly a convenience function to avoid having client code refer directly
	 * to the TokenLayerFactory instance.
	 *
	 * @param class_id the unique class identifier
	 * @param input the input source to pass to the layer's constructor
	 */
	static TokenLayer* create(const std::string class_id,
	                          TokenSource* input,
	                          const Properties& props);

	/**
	 * Convenience template for registering TokenLayer derived classes.
	 */
	template <typename T>
	static bool register_layer(const std::string& class_id);

protected:
	virtual Token* getTokenFromInput();

	bool shouldProcessTokenType(const std::string& t);

private:
	/**
	 * Pointer to the source TokenSource (e.g. a layer). No ownership.
	 */
	TokenSource* input_;

	std::set<std::string> process_token_types_;

	std::set<std::string> do_not_process_token_types_;
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
		Loki::TL::MakeTypelist< TokenSource*, const TokenLayer::Properties& >::Result
		// TokenLayer constructor arguments' types specification
	>,
	Loki::CreateUsingNew, // Default, needed to change the item below
	Loki::LongevityLifetime::DieAsSmallObjectChild // Required per libloki docs
>
TokenLayerFactory;

/**
 * Convenience typedef for the exception type the factory throws
 */
typedef Loki::DefaultFactoryError<
	std::string, TokenLayer
>::Exception
TokenLayerFactoryException;

/**
 * Convenience template TokenLayer creation function
 */
template <typename T>
inline
T* LayerCreator(TokenSource* input, const TokenLayer::Properties& props)
{
	return new T(input, props);
}

#include <iostream>
template <typename T>
bool TokenLayer::register_layer(const std::string& class_id)
{
	std::cout << "Register layer type '" << class_id << "'";
	bool ret = TokenLayerFactory::Instance().Register(class_id, LayerCreator<T>);
	if (ret) std::cout << " (ok)";
	std::cout << "\n";
	return ret;
}


#endif // TOKENLAYER_H
