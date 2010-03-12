#ifndef UNICODESOURCE_H
#define UNICODESOURCE_H

#include <unicode/utypes.h>

class UnicodeSource
{
public:
    UnicodeSource() {}
    virtual ~UnicodeSource() {}

    virtual UChar peekNextChar() = 0;

    virtual UChar getNextChar() = 0;

    virtual bool hasMoreChars() = 0;
};

#endif // UNICODESOURCE_H
