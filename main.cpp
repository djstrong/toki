#include "tokenizer.h"
#include "icustreamwrapper.h"
#include "icustringsource.h"
#include <iostream>
#include <sstream>
#include <unicode/ustream.h>



int main()
{
    Token tok("arghżźć", "a", Token::WA_None);
    std::cout << tok.orth().length() << " " << tok.orth_utf8().size() << "\n";
    std::cout << tok.orth_utf8();

    {
        std::stringstream ss;
        ss << "asasa s   sasa ";
        UnicodeString us;
        ss >> us;
        std::cout << us << "!\n";
        ss >> us;
        std::cout << us << "!\n";
        ss >> us;
        std::cout << us << "!\n";
    }
    const char test[] = "ŻŻŻas żźŻŹół  Ę  \nxx\n\nZżźŻŹ \n";
    IcuStringSource iss(UnicodeString::fromUTF8(test));
    Tokenizer tkz(iss);
    tkz.debug_tokenize();

    std::stringstream ss4;
    ss4 << test;
    IcuStreamWrapper isw2(ss4, 1);
    Tokenizer tkz2(isw2);
    tkz2.debug_tokenize();

    std::stringstream ss3;
    ss3 << "zfg ążÓŁx";
    IcuStreamWrapper isw(ss3, 1);
    std::cout << ">>";
    while (isw.hasMoreChars()) {
        UChar u = isw.getNextChar();
        UnicodeString us(u);
        std::string s;
        std::cout << us.toUTF8String(s);
    }
    std::cout << "\n";

}
