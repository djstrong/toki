#include "tokenizer.h"
#include "icustreamwrapper.h"
#include "icustringsource.h"
#include <iostream>
#include <sstream>
#include <unicode/ustream.h>

#include <boost/program_options.hpp>

void test1()
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



int main(int argc, char** argv)
{
    std::string input_enc;
    int bufsize;
    using boost::program_options::value;
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
//            ("input-encoding,e", value(&input_enc)->default_value("utf8"), "Input encoding")
            ("buffer-size,b", value(&bufsize)->default_value(200), "Stream buffer size, set to 0 to convert the entire input in-memory")
            ;
    boost::program_options::variables_map vm;

    try {
        boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
    } catch (boost::program_options::error& e) {
        std::cerr << e.what() << "\n";
        return 2;
    }
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    UnicodeString us;
    if (bufsize > 0) {
        IcuStreamWrapper isw(std::cin, bufsize);
        while (isw.hasMoreChars()) {
            UChar u = isw.getNextChar();
            us += u;
        }
    } else {
        std::stringstream ss;
        ss << std::cin.rdbuf();
        IcuStringSource iss(UnicodeString::fromUTF8(ss.str()));
        while (iss.hasMoreChars()) {
            UChar u = iss.getNextChar();
            us += u;
        }
    }
    std::string u8;
    std::cout << us.toUTF8String(u8);
}
