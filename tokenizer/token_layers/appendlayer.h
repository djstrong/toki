#ifndef APPENDLAYER_H
#define APPENDLAYER_H

#include "tokenlayer.h"
#include <unicode/unistr.h>

/**
 * A sample layer that appends a constant bit of text to the orth of each token.
 */
class AppendLayer : public TokenLayer
{
public:
	/**
	 * Constructor.
	 *
	 * Keys recognized in the configuration:
	 * - append - text to append, treated as UTF-8 and unescaped. Defaults to
	 *            an exlamation mark (!).
	 */
	AppendLayer(TokenSource* input, const Properties& props);

	/// TokenLayer override
	Token* processToken(Token *t);

private:
	/// The string to append
	UnicodeString append_;
};

#endif // APPENDLAYER_H
