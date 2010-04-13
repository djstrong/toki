#ifndef LIBTOKI_APPENDLAYER_H
#define LIBTOKI_APPENDLAYER_H

#include "tokenlayer.h"
#include <unicode/unistr.h>

namespace Toki {

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
		 * - append - Text to append, treated as UTF-8 and unescaped. Defaults to
		 *            an exlamation mark (!).
		 */
		AppendLayer(TokenSource* input, const Config::Node& props);

		/// TokenLayer override
		Token* processToken(Token *t);

		/// TokenLayer override
		virtual std::string info() const;

		/// TokenLayer override
		std::string long_info() const;
	private:
		/// The string to append
		UnicodeString append_;
	};

} //end namespace Toki

#endif // LIBTOKI_APPENDLAYER_H
