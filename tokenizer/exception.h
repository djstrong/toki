#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

/**
 * Base class for all tokenizer errors. Derives from
 * @c std::runtime_error. Call member function @c what to get a
 * human-readable message associated with the error.
 */
class TokenizerLibError : public std::runtime_error
{
public:
	/**
	 * Instantiate a TokenizerLibError instance with the given message.
	 * @param what The message to associate with this error.
	 */
	TokenizerLibError(const std::string &what)
	 : std::runtime_error(what)
	{
	}

	~TokenizerLibError() throw()
	{
	}
};

/**
 * Class to signify "can't happen" errors
 */
class TokenizerImpossibleError : public TokenizerLibError
{
public:
	TokenizerImpossibleError(const std::string &what)
	 : TokenizerLibError(what)
	{
	}

	~TokenizerImpossibleError() throw()
	{
	}
};

#endif // EXCEPTION_H
