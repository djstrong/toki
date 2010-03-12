#ifndef ICUSTRINGSOURCE_H
#define ICUSTRINGSOURCE_H
#include <unicode/unistr.h>
#include <unicode/schriter.h>

#include "unicodesource.h"

class IcuStringSource : public UnicodeSource
{
public:
	IcuStringSource(const UnicodeString& u);

	UChar peekNextChar();

	UChar getNextChar();

	bool hasMoreChars();

private:
	StringCharacterIterator iter_;
};

#endif // ICUSTRINGSOURCE_H
