#ifndef NULLUNICODESOURCE_H
#define NULLUNICODESOURCE_H

#include "unicodesource.h"

#include "exception.h"

class NullUnicodeSource : public UnicodeSource
{
public:
	NullUnicodeSource() {}

	/// UnicodeSource override
	UChar peekNextChar() {
		throw TokenizerImpossibleError("NullUnicodeSource::peekNextChar called");
		return 0;
	}

	/// UnicodeSource override
	UChar getNextChar() {
		throw TokenizerImpossibleError("NullUnicodeSource::getNextChar called");
		return 0;
	}

	/// UnicodeSource override
	bool hasMoreChars() {
		return false;
	}
};

#endif // NULLUNICODESOURCE_H
