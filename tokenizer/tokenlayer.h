#ifndef TOKENLAYER_H
#define TOKENLAYER_H

#include "tokensource.h"
#include "config.h"

#include <boost/utility.hpp>
#include <loki/Factory.h>
#include <loki/Singleton.h>

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
	/**
	 * The constructor.
	 * @param input The token source this layer will process tokens from.
	 * @param props Configuration of the token layer.
	 *
	 * Keys recognized in the configuration:
	 * - process_types - Space-separated list of token types to include in
	 *                   processing. All tokens are considered if it is empty.
	 *                   Defaults to empty.
	 * - ignore_types  - Space-separated list of token types to explicitly
	 *                   ignore, even if they pass the process_types check.
	 *                   Defaults to empty.
	 */
	TokenLayer(TokenSource* input, const Config::Node& props);

	/// The destructor
	virtual ~TokenLayer();

	/**
	 * Getter for the input source.
	 */
	TokenSource* getInput();

	/**
	 * TokenSource override. Default implementation for layers that only work
	 * by examining a single token and possibly modyfying it -- grabs a token
	 * from the input, examines it for NULL and shouldProcessTokenType, calls
	 * @c processToken and returns whatever that function returns.
	 */
	Token* getNextToken();

	/**
	 * Used by the default getNextToken implementation, should be overriden by
	 * derived classes. Defaults to a no-op passthrough of the token.
	 * @param t token to process. Guaranteed to be not-NULL.
	 */
	virtual Token* processToken(Token* t);

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
	 * Return a short string with some human-readable info about this layer
	 */
	virtual std::string info() const;

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
	                          const Config::Node& props);

	/**
	 * Debug function to get a vector of available layer type strings.
	 */
	static std::vector<std::string> available_layer_types();

	/**
	 * Convenience template for registering TokenLayer derived classes.
	 */
	template <typename T>
	static bool register_layer(const std::string& class_id);

protected:
	/**
	 * Convenience helper to avoid having derived classes access the input
	 * source directly
	 */
	virtual Token* getTokenFromInput();

	/**
	 * Determine if the given token type should be processed according to
	 * process / ignore rules
	 */
	bool shouldProcessTokenType(const std::string& t);

private:
	/**
	 * Pointer to the source TokenSource (e.g. a layer). No ownership.
	 */
	TokenSource* input_;

	/**
	 * Set of token types to process, if empty, all are considered
	 */
	std::set<std::string> process_token_types_;

	/**
	 * Set of token types to ignore, checked after they pass the inclusion check
	 */
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
		Loki::TL::MakeTypelist< TokenSource*, const Config::Node& >::Result
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
T* LayerCreator(TokenSource* input, const Config::Node& props)
{
	return new T(input, props);
}

#include <iostream>
template <typename T>
bool TokenLayer::register_layer(const std::string& class_id)
{
	bool ret = TokenLayerFactory::Instance().Register(class_id, LayerCreator<T>);
	return ret;
}


#endif // TOKENLAYER_H
