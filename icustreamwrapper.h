#ifndef ICUSTREAMWRAPPER_H
#define ICUSTREAMWRAPPER_H

#include "unicodesource.h"
#include <istream>
#include <unicode/unistr.h>
#include <unicode/ucnv.h>

class IcuStreamWrapper : public UnicodeSource
{
public:
    IcuStreamWrapper(std::istream& is, int buf_size = 200);
    ~IcuStreamWrapper();

    UChar peekNextChar();

    UChar getNextChar();

    bool hasMoreChars();

private:
    void more();

    std::istream& is_;
    UConverter* converter_;
    int buf_size_;
    char* source_buf_;
    UChar* target_buf_;
    UChar* target_;
    UChar* target_limit_;
    UErrorCode err_;
    UChar* out_;
};

#endif // ICUSTREAMWRAPPER_H
