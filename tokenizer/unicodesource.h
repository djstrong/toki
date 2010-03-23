#ifndef UNICODESOURCE_H
#define UNICODESOURCE_H

#include <unicode/utypes.h>

/**
 * This class represents something that we can get ICU Unicode characters from
 * and is generally used to abstract away a bit of the functionality we need
 * from a ICU-Unicode wrapper for an input stream.
 *
 * It is similar to ICU's ForwardCharacterIterator, but we probably don't want
 * to inherit directly from ICU, and we want the extra "peek" functionality.
 */
class UnicodeSource
{
public:

	/// Constructor
	UnicodeSource() {}

	/// Destructor
	virtual ~UnicodeSource() {}

	/**
	 * Peek the next character, that is, return it without advancing to the next
	 * character.
	 *
	 * This function might change the internal status to make sure there is
	 * something available for returning, so it cannot be const.
	 *
	 * @return the next character to be returned, or 0x0 if there is none.
	 *         Calling code should generally check hasMoreChars() first.
	 */
	virtual UChar peekNextChar() = 0;

	/**
	 * Get the next character. Functionally similar to peekNextChar that
	 * advances internally to the next character.
	 *
	 * @return the next character to be returned, or 0x0 if there is none.
	 *         Calling code should generally check hasMoreChars() first.
	 */
	virtual UChar getNextChar() = 0;

	/**
	 * Check if there will be more characters to return.
	 *
	 * This function might change the internal status to make sure there is
	 * something available for returning, so it cannot be const.
	 *
	 * @return true if there is something to return, false otherwise.
	 */
	virtual bool hasMoreChars() = 0;
};

#endif // UNICODESOURCE_H
