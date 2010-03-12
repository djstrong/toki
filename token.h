#ifndef TOKEN_H
#define TOKEN_H

#include <unicode/unistr.h>
#include <string>

class Token
{
public:
    enum WhitespaceAmount {
        WA_None,
        WA_Space,
        WA_ManySpaces,
        WA_Newline,
        WA_ManyNewlines
    };

    Token(const UnicodeString& orth, const std::string& type, WhitespaceAmount wa_before);

    Token(const char* orth_utf8, const std::string& type, WhitespaceAmount wa_before);

    const UnicodeString& orth() const {
        return orth_;
    }

    const std::string& type() const {
        return type_;
    }

    WhitespaceAmount preceeding_whitespace() const {
        return preceeding_whitespace_;
    }

    std::string orth_utf8() const;

    std::string debugUtf8() const;

protected:
    UnicodeString orth_;
    std::string type_;
    WhitespaceAmount preceeding_whitespace_;
};

#endif // TOKEN_H
