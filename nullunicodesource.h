#ifndef NULLUNICODESOURCE_H
#define NULLUNICODESOURCE_H

#include "unicodesource.h"

class NullUnicodeSource : public UnicodeSource
{
public:
	NullUnicodeSource() {}

	/// UnicodeSource override
	UChar peekNextChar() {
		return 0;
	}

	/// UnicodeSource override
	UChar getNextChar() {
		return 0;
	}

	/// UnicodeSource override
	bool hasMoreChars() {
		return false;
	}
};

#endif // NULLUNICODESOURCE_H
