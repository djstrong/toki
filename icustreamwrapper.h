#ifndef ICUSTREAMWRAPPER_H
#define ICUSTREAMWRAPPER_H

#include "unicodesource.h"
#include <istream>
#include <unicode/unistr.h>
#include <unicode/ucnv.h>

class IcuStreamWrapper : public UnicodeSource
{
public:
    IcuStreamWrapper(std::istream& is, int buf_size = 200,
                     const char* input_encoding = "UTF8");
    ~IcuStreamWrapper();

    UChar peekNextChar();

    UChar getNextChar();

    UnicodeString getBuffer();

    bool hasMoreChars();

private:
    /*
     * Read a next batch of characters from the source stream, convert it
     * and store in the target buffer so characters can be returned by
     * get/peekNextChar.
     *
     * @return the number of characters read from the input stream
     */
    int more();

    /*
     * For very small buffer sizes (<4) it is possible that a single more()
     * call will not be enough to end up with at least one character in the
     * target buffer, confusing other code. This function takes care to call
     * more() repeatedly until at least one character ends up in the target
     * buffer.
     */
    void ensure_more();

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
